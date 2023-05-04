#ifndef _GITHUBREPOSYNC_H
#define _GITHUBREPOSYNC_H


#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QApplication>

class TrivTask : public QObject {
Q_OBJECT
public :
    TrivTask() : started(false), finished(false) { }

    bool isStarted() { return started; }
    bool isFinished() { return finished; }

public slots:

    void start() {
        if (!started)
        {
            started = true;
            funcStart();
            emit onStart();
        }
    }

    void finish() {
        if (!started)
            return;

        if (!finished) {
            finished = true;
            funcFinish();
            emit onFinish();
        }
    }

    void update() {
        if (started && !finished) {
            funcUpdate();
            emit onUpdate();
        }

        QObjectList childs = this->children();

        for (QObject* child : childs) {
            TrivTask* child_task = qobject_cast<TrivTask*>(child);
                child_task->update();
        }
    }

signals:
    void onStart();
    void onUpdate();
    void onFinish();

protected:
    virtual void funcStart() {  }
    virtual void funcFinish() {  }
    virtual void funcUpdate() { }

private:
    bool started;
    bool finished;
};

class TrivTaskManager : public QObject {
Q_OBJECT
public:
    TrivTaskManager(int _updateInterval) : updateInterval(_updateInterval) {

    }

public slots:
    void update() {
        QObjectList childs = this->children();

        for (QObject* child : childs) {
            TrivTask* child_task = qobject_cast<TrivTask*>(child);
                child_task->update();
        }

    }

private:
    int updateInterval;
};

class FileOp {
public:
    enum Operation {
        OP_ADD,
        OP_MOD,
        OP_DEL,
        OP_GET
    };

    FileOp(Operation _op, QString _repoPath, QString _localPath, QString _sha) : op(_op), repoPath(_repoPath), localPath(_localPath), sha(_sha) { }

    Operation op;
    QString repoPath;
    QString localPath;
    QString sha;
};

class FileStat {
public:
    QString path;
    QString sha;
    qint64 size;
};


class GHRSGetLocalFileStat : public QObject {
    Q_OBJECT
public:

};

class GHRSGetServerFileStat : public QObject {
    Q_OBJECT
public:

};


class GitHubRepoSync : public QObject {
Q_OBJECT
public:

    GitHubRepoSync(const QString& _username, const QString& _reponame, const QString& _token, const QString& _localDir) :
        username(_username), reponame(_reponame), token(_token), localDir(_localDir) {

    }

    void get() {
        // run in thread output: localFileStat
        getLoacalFileStat();

        //httprequest output: serverFileStat
        getServerFileStat();

        // input: localFileStat, serverFileStat output: getFileOp
        createGetOperations();

        // input List<FileOp>
        //exeOperations();
    }

    void put() {
        getLoacalFileStat();
        getServerFileStat();

        createPutOperations();
    }

private:
    QString username;
    QString reponame;
    QString token;
    QString localDir;

    QList<FileStat> localFileStat;
    QList<FileStat> serverFileStat;

    QList<FileOp> operations;

    void getLoacalFileStat() {
        localFileStat.clear();
    }

    void getServerFileStat() {
        serverFileStat.clear();
    }

    void createGetOperations() {

    }

    void createPutOperations() {

    }

};



class Repo : public QObject {
Q_OBJECT
public:
    Repo(const QString& _username, const QString& _reponame, const QString& _token) : username(_username), reponame(_reponame), token(_token) {

    }

    void repoPut(QList<FileOp>& opList, const QString& commitMessage ) {

        // dodajemy blob
        for (FileOp& op : opList) {
            if (op.op == FileOp::OP_ADD || op.op == FileOp::OP_MOD) {
                op.sha = repoAddBlob(op.localPath);
            }
        }

        QString mainSha = repoGetHeadMain();

        // tworzymy tree
        QJsonArray files;

        for (FileOp& op : opList) {
            QJsonObject file;
            file.insert("path", op.repoPath);
            file.insert("mode", "100644");
            file.insert("type", "blob");

            if (op.op == FileOp::OP_DEL) {
                file.insert("sha", QJsonValue(QJsonValue::Null));
            } else {
                file.insert("sha", op.sha);
            }

            files.append(file);
        }

        QJsonObject tree;
        tree.insert("base_tree", mainSha);
        tree.insert("tree", files);

        QJsonDocument treeDoc(tree);
        QByteArray treeData = treeDoc.toJson(QJsonDocument::Compact);

        QNetworkAccessManager manager;

        QNetworkRequest request(QUrl(QUrl("https://api.github.com/repos/"  + username + "/" + reponame + "/git/trees")));
        request.setRawHeader("Authorization", (QString("Bearer ") + token).toUtf8());
        request.setRawHeader("Accept", "application/vnd.github.v3+json");

        QNetworkReply *treeReply = manager.post(request, treeData);

        while (!treeReply->isFinished()) {
            QApplication::processEvents();
        }

        if (treeReply->error() == QNetworkReply::NoError) {
            qDebug() << "Tree Create successfully";

            QByteArray data = treeReply->readAll();
            QJsonDocument doc = QJsonDocument::fromJson(data);
            QString treeSha = doc.object().value("sha").toString();

            QJsonObject commit;
            commit.insert("message", commitMessage);
            commit.insert("parents", QJsonArray({mainSha}));
            commit.insert("tree", treeSha);

            /*
            QJsonObject author;
            author.insert("name", "Your Name");
            author.insert("email", "yourname@example.com");
            commit.insert("author", author);
            */

            QJsonDocument commitDoc(commit);
            QByteArray commitData = commitDoc.toJson(QJsonDocument::Compact);

            request.setUrl(QUrl("https://api.github.com/repos/" + username + "/" + reponame + "/git/commits"));
            QNetworkReply *commitReply = manager.post(request, commitData);

            while (!commitReply->isFinished()) {
                QApplication::processEvents();
            }

            if (commitReply->error() == QNetworkReply::NoError) {
                qDebug() << "Commit successfully";

                QByteArray data = commitReply->readAll();
                QJsonDocument doc = QJsonDocument::fromJson(data);
                QString commitSha = doc.object().value("sha").toString();

                QJsonObject ref;
                ref.insert("sha", commitSha);

                QJsonDocument refDoc(ref);
                QByteArray refData = refDoc.toJson(QJsonDocument::Compact);

                request.setUrl(QUrl("https://api.github.com/repos/" + username + "/" + reponame + "/git/refs/heads/main"));
                QNetworkReply *refReply = manager.sendCustomRequest(request, "PATCH", refData);

                while (!refReply->isFinished()) {
                    QApplication::processEvents();
                }

                if (commitReply->error() == QNetworkReply::NoError) {
                    qDebug() << "Ref successfully";
                } else {
                    qDebug() << "Error updating ref:" << commitReply->errorString();
                }

                refReply->deleteLater();
            }else {
                qDebug() << "Error creating commit:" << commitReply->errorString();
            }

            commitReply->deleteLater();
        } else {
            qDebug() << "Error creating tree:" << treeReply->errorString();
        }

        treeReply->deleteLater();
    }

    QString repoAddBlob(const QString& localFileNmae) {
        QFile file(localFileNmae);
        file.open(QIODevice::ReadOnly);

        QByteArray content = file.readAll();
        QString encodedContent = content.toBase64();

        QNetworkRequest request(QUrl(QString("https://api.github.com/repos/") + username + "/" + reponame + "/git/blobs"));
        request.setRawHeader("Authorization", (QString("Bearer ") + token).toUtf8());
        request.setRawHeader("Accept", "application/vnd.github.v3+json");

        QJsonDocument doc;
        QJsonObject json;
        json.insert("content", encodedContent);
        json.insert("encoding", "base64");
        doc.setObject(json);
        QByteArray data = doc.toJson(QJsonDocument::Compact);

        QNetworkAccessManager manager;
        QNetworkReply *reply = manager.post(request, data);

        while (!reply->isFinished()) {
            QApplication::processEvents();
        }

        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "Blob add successfully";
            QByteArray data = reply->readAll();
            QJsonDocument doc = QJsonDocument::fromJson(data);
            QString blobSha = doc.object().value("sha").toString();
            reply->deleteLater();

            return blobSha;
        } else {
            qDebug() << "Error blob add:" << reply->errorString();
        }

        reply->deleteLater();
        return "";
    }

    QString repoGetHeadMain() {
        // Pobranie SHA1 drzewa plików z najnowszego commita w gałęzi "main"
        QString ref = "heads/main";
        QNetworkRequest request(QUrl(QString("https://api.github.com/repos/") + username + "/" + reponame+ "/git/ref/" + ref));
        request.setRawHeader("Authorization", (QString("Bearer ") + token).toUtf8());
        request.setRawHeader("Accept", "application/vnd.github+json");

        QString sha;

        QNetworkAccessManager manager;

        QNetworkReply *reply = manager.get(request);

        while (!reply->isFinished()) {
            QApplication::processEvents();
        }

        if (reply->error() == QNetworkReply::NoError) {

            qDebug() << "repoGetHeadMain SUCCESS";

            QByteArray data = reply->readAll();
            QJsonDocument doc = QJsonDocument::fromJson(data);
            sha = doc.object().value("object").toObject().value("sha").toString();
        } else {
            qDebug() << "repoGetHeadMain Error:" << reply->errorString();
        }

        reply->deleteLater();

        return sha;
    }



    void repoCommit1() {

        // Utworzenie plik
        QString path1 = "dir1/file1.txt";
        QByteArray fileContent1 = "Hello, World! from file1";
        QString encodedContent1 = fileContent1.toBase64();

        // Modyfikacja pliku
        QString path2 = "dir1/file2.txt";
        QByteArray fileContent2 = "Hello, World! from file2";
        QString encodedContent2 = fileContent2.toBase64();

        // Usunięcie pliku
        QString path3 = "dir_test2/plik1.txt";

        // plik do dodania
        QString fileSha4 = repoAddBlob("D:/test_plik1.txt");
        QString path4 = "file4.txt";

        // Pobranie SHA1 drzewa plików z najnowszego commita w gałęzi "main"
        QString ref = "refs/heads/main";
        QNetworkRequest request(QUrl(QString("https://api.github.com/repos/") + username + "/" + reponame+ "/git/ref/" + ref));
        request.setRawHeader("Authorization", (QString("Bearer ") + token).toUtf8());
        request.setRawHeader("Accept", "application/vnd.github.v3+json");


        QNetworkAccessManager manager;

        QNetworkReply *reply = manager.get(request);

        while (!reply->isFinished()) {
            QApplication::processEvents();
        }

        if (reply->error() == QNetworkReply::NoError) {

            QByteArray data = reply->readAll();
            QJsonDocument doc = QJsonDocument::fromJson(data);
            QString sha = doc.object().value("object").toObject().value("sha").toString();

            //QString sha = "d1d3a7a55f67ae384c8a628335fc5cecfd21aa43";//"2331ec90547187f772bc166e4205515cdebaa2aa";//"0674a04f1ab898e79ca7cddce825b0bacdf2f783"; //"2331ec90547187f772bc166e4205515cdebaa2aa"; // ////repoGetTreeSha();


            // Utworzenie nowego drzewa plików
            QJsonObject file1;
            file1.insert("path", path1);
            file1.insert("mode", "100644");
            file1.insert("content", encodedContent1);

            QJsonObject file2;
            file2.insert("path", path2);
            file2.insert("mode", "100644");
            file2.insert("content", encodedContent2);


            QJsonObject deleteFile;
            deleteFile.insert("path", path2);
            deleteFile.insert("mode", "100644");
            deleteFile.insert("type", "blob");
            deleteFile.insert("sha", QJsonValue(QJsonValue::Null)); // ustawienie pustego SHA1 spowoduje usunięcie pliku

            QJsonObject file4;
            file4.insert("path", path2);
            file4.insert("mode", "100644");
            file4.insert("type", "blob");
            file4.insert("sha", fileSha4);

            QJsonArray files;
            files.append(file1);
            files.append(file2);
            files.append(deleteFile);
            //files.append(file4);

            QJsonObject tree;
            tree.insert("base_tree", sha);
            tree.insert("tree", files);

            QJsonDocument treeDoc(tree);
            QByteArray treeData = treeDoc.toJson(QJsonDocument::Compact);

            // Utworzenie nowego drzewa plików
            request.setUrl(QUrl("https://api.github.com/repos/"  + username + "/" + reponame + "/git/trees"));
            QNetworkReply *treeReply = manager.post(request, treeData);

            while (!treeReply->isFinished()) {
                QApplication::processEvents();
            }

            if (treeReply->error() == QNetworkReply::NoError) {
                QByteArray data = treeReply->readAll();
                QJsonDocument doc = QJsonDocument::fromJson(data);
                QString treeSha = doc.object().value("sha").toString();

                qDebug() << "!!!" << treeSha;

                QJsonObject commit;
                commit.insert("message", "Add, modify and delete files");
                commit.insert("parents", QJsonArray({sha}));
                commit.insert("tree", treeSha);

                /*
                QJsonObject author;
                author.insert("name", "Your Name");
                author.insert("email", "yourname@example.com");
                commit.insert("author", author);
                */

                QJsonDocument commitDoc(commit);
                QByteArray commitData = commitDoc.toJson(QJsonDocument::Compact);

                request.setUrl(QUrl("https://api.github.com/repos/" + username + "/" + reponame + "/git/commits"));
                QNetworkReply *commitReply = manager.post(request, commitData);

                while (!commitReply->isFinished()) {
                    QApplication::processEvents();
                }

                if (commitReply->error() == QNetworkReply::NoError) {
                    qDebug() << "Commit successfully";

                    QByteArray data = commitReply->readAll();
                    QJsonDocument doc = QJsonDocument::fromJson(data);
                    QString commitSha = doc.object().value("sha").toString();

                    QJsonObject ref;
                    ref.insert("sha", commitSha);

                    QJsonDocument refDoc(ref);
                    QByteArray refData = refDoc.toJson(QJsonDocument::Compact);

                    request.setUrl(QUrl("https://api.github.com/repos/" + username + "/" + reponame + "/git/refs/heads/main"));
                    QNetworkReply *refReply = manager.sendCustomRequest(request, "PATCH", refData);

                    while (!refReply->isFinished()) {
                        QApplication::processEvents();
                    }

                    if (commitReply->error() == QNetworkReply::NoError) {
                        qDebug() << "Ref successfully";
                    } else {
                        qDebug() << "Error udpating ref:" << commitReply->errorString();
                    }

                    refReply->deleteLater();

                } else {
                    qDebug() << "Error creating commit:" << commitReply->errorString();
                }

                commitReply->deleteLater();
            } else {
                qDebug() << "Error creating tree:" << treeReply->errorString();
            }

            treeReply->deleteLater();
        } else {
            qDebug() << "Error getting latest commit:" << reply->errorString();
        }

        reply->deleteLater();
    }


    /*
    // dodaje 2 pliki "dir1/file1.txt" i "dir1/file2.txt"
    void repoCommit1() {
        QByteArray fileContent1 = "Hello, World! from file1";
        QByteArray fileContent2 = "Hello, World! from file2";
        QString encodedContent1 = fileContent1.toBase64();
        QString encodedContent2 = fileContent2.toBase64();
        QString filepath1 = "dir1/file1.txt";
        QString filepath2 = "dir1/file2.txt";

        QString tree_sha = repoGetTreeSha();
        qDebug() << "tree_sha=" << tree_sha;

        QNetworkRequest request(QUrl(QString("https://api.github.com/repos/") + username + "/" + reponame + "/git/commits"));
        request.setRawHeader("Authorization", (QString("Bearer ") + token).toUtf8());
        request.setRawHeader("Accept", "application/vnd.github.v3+json");

        QJsonObject file1;
        file1.insert("path", filepath1);
        file1.insert("mode", "100644");
        file1.insert("type", "blob");
        file1.insert("content", encodedContent1);

        QJsonObject file2;
        file2.insert("path", filepath2);
        file2.insert("mode", "100644");
        file2.insert("type", "blob");
        file2.insert("content", encodedContent2);

        QJsonArray files;
        files.append(file1);
        files.append(file2);

        QJsonObject json;
        json.insert("message", "Add files");
        json.insert("author", QJsonObject{{"name", "Your Name"}, {"email", "your.email@example.com"}});
        json.insert("parents", QJsonArray{QJsonObject{{"sha", "HEAD"}}});
        json.insert("tree", QJsonObject{{"sha", tree_sha}});
        json.insert("changes", QJsonObject{{"files", files}});
        QJsonDocument doc(json);
        QByteArray data = doc.toJson(QJsonDocument::Compact);

        QNetworkAccessManager manager;
        QNetworkReply *reply = manager.post(request, data);

        while (!reply->isFinished()) {
            QApplication::processEvents();
        }

        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "commit1 SUCCESS";
        } else {
            qDebug() << "Error commit1 file:" << reply->errorString();
        }

        reply->deleteLater();
    }
    */





    /*

    void repoAddFile(const QString& localFilename, const QString& repoFileName) {
        QFile file(localFilename);
        file.open(QIODevice::ReadOnly);

        QByteArray content = file.readAll();
        QString encodedContent = content.toBase64();


                QNetworkRequest request(QUrl(QString("https://api.github.com/repos/") + username + QString("/") + reponame + QString("/git/commits")));
                request.setRawHeader("Authorization", (QString("Bearer ") + token).toUtf8());
                request.setRawHeader("Accept", "application/vnd.github.v3+json");

                QJsonDocument doc;
                QJsonObject json;
                json.insert("message", "Add new file");
                json.insert("content", encodedContent);
                QJsonObject tree;
                tree.insert("path", repoFileName);
                tree.insert("mode", "100644");
                tree.insert("type", "blob");
                tree.insert("content", encodedContent);
                QJsonArray arr;
                arr.append(tree);
                json.insert("tree", arr);
                doc.setObject(json);
                QByteArray data = doc.toJson(QJsonDocument::Compact);

                QNetworkAccessManager manager;
                QNetworkReply *reply = manager.post(request, data);

                while (!reply->isFinished()) {
                    QApplication::processEvents();
                }

                if (reply->error() == QNetworkReply::NoError) {
                    qDebug() << "File added successfully";
                } else {
                    qDebug() << "Error adding file:" << reply->errorString();
                }

                reply->deleteLater();
    }
*/

    // dodaje nowy plik tworzy katalogi jak trzeba
    // !!! nie modyfikuje pliku
    void repoAddFile(const QString& localFilename, const QString& repoFileName) {
        QFile file(localFilename);
        file.open(QIODevice::ReadOnly);

        QByteArray content = file.readAll();
        QString encodedContent = content.toBase64();

        QNetworkRequest request(QUrl(QString("https://api.github.com/repos/") + username + QString("/") + reponame + QString("/contents/") + repoFileName));
        request.setRawHeader("Authorization", (QString("Bearer ") + token).toUtf8());
        request.setRawHeader("Accept", "application/vnd.github.v3+json");
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QJsonDocument doc;
        QJsonObject json;
        json.insert("message", "Add new file");
        json.insert("content", encodedContent);
        doc.setObject(json);
        QByteArray data = doc.toJson(QJsonDocument::Compact);

        QNetworkAccessManager manager;
        QNetworkReply *reply = manager.put(request, data);

        while (!reply->isFinished()) {
            QApplication::processEvents();
        }

        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "File added/modified successfully";
        } else {
            qDebug() << "Error adding/modifying file:" << reply->errorString();
        }

        reply->deleteLater();

    }

    void repoDeleteFile(const QString& filename, const QString& localFilename) {
        QString sha = getShaOfFile(localFilename);
        QNetworkRequest request(QUrl(QString("https://api.github.com/repos/") + username + QString("/") + reponame + QString("/contents/") + filename));
        request.setRawHeader("Authorization", (QString("Bearer ") + token).toUtf8());
        request.setRawHeader("Accept", "application/vnd.github.v3+json");

        QJsonDocument doc;
        QJsonObject json;
        json.insert("message", "Delete file");
        json.insert("sha", sha);
        doc.setObject(json);
        QByteArray data = doc.toJson(QJsonDocument::Compact);

        QNetworkAccessManager manager;
        QNetworkReply *reply = manager.sendCustomRequest(request, "DELETE", data);
                //.deleteResource(request);

        while (!reply->isFinished()) {
            QApplication::processEvents();
        }

        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "File deleted successfully";
        } else {
            qDebug() << "Error deleting file:" << reply->errorString();
        }

        reply->deleteLater();

    }

    QString repoGetTreeSha() {
        QNetworkAccessManager manager;
        QString baseUrl = QString("https://api.github.com/repos/") + username + QString("/") + reponame + QString("/commits");
        QUrl url(baseUrl);
        QNetworkRequest request(url);

        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setRawHeader("Authorization", (QString("Bearer ") + token).toUtf8());
        request.setRawHeader("Accept", "application/vnd.github.v3+json");

        QNetworkReply *reply = manager.get(request);
        while (!reply->isFinished()) {
            QApplication::processEvents();
        }

        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonArray contents = doc.array();
        QJsonObject shaObject = contents.first().toObject();
        QString sha = shaObject.value("sha").toString();

        return sha;
    }

    void repoListAllFiles() {
        QNetworkAccessManager manager;
        QString baseUrl = QString("https://api.github.com/repos/") + username + QString("/") + reponame + QString("/commits");
        QUrl url(baseUrl);
        QNetworkRequest request(url);

        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setRawHeader("Authorization", (QString("Bearer ") + token).toUtf8());
        request.setRawHeader("Accept", "application/vnd.github.v3+json");

        QNetworkReply *reply = manager.get(request);
        while (!reply->isFinished()) {
            QApplication::processEvents();
        }

        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonArray contents = doc.array();
        QJsonObject shaObject = contents.first().toObject();
        QString sha = shaObject.value("sha").toString();

        baseUrl = QString("https://api.github.com/repos/") +  username + QString("/") + reponame + QString("/git/trees/") + sha + QString("?recursive=1");
        url = QUrl(baseUrl);
        request.setUrl(url);
        reply = manager.get(request);
        while (!reply->isFinished()) {
            QApplication::processEvents();
        }

        doc = QJsonDocument::fromJson(reply->readAll());
        QJsonArray files = doc.object().value("tree").toArray();

        foreach (const QJsonValue &value, files) {
            QString path = value.toObject().value("path").toString();
            QString sha = value.toObject().value("sha").toString();
            QString type = value.toObject().value("type").toString();

            if (type == "blob") {
                QString fileChecksum = value.toObject().value("sha").toString();
                qDebug() << "File name:" << path << ", Checksum:" << fileChecksum;
            }
        }
    }

    QString repoGetShaOfFilInLastCommit(const QString& filepath) {
        QNetworkAccessManager manager;
        QString baseUrl = QString("https://api.github.com/repos/") + username + QString("/") + reponame + QString("/commits");
        QUrl url(baseUrl);
        QNetworkRequest request(url);

        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setRawHeader("Authorization", (QString("Bearer ") + token).toUtf8());
        request.setRawHeader("Accept", "application/vnd.github.v3+json");

        QNetworkReply *reply = manager.get(request);
        while (!reply->isFinished()) {
            QApplication::processEvents();
        }

        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonArray contents = doc.array();
        QJsonObject shaObject = contents.first().toObject();
        QString sha = shaObject.value("sha").toString();

        baseUrl = QString("https://api.github.com/repos/") +  username + QString("/") + reponame + QString("/git/trees/") + sha + QString("?recursive=1");
        url = QUrl(baseUrl);
        request.setUrl(url);
        reply = manager.get(request);
        while (!reply->isFinished()) {
            QApplication::processEvents();
        }

        doc = QJsonDocument::fromJson(reply->readAll());
        QJsonArray files = doc.object().value("tree").toArray();

        foreach (const QJsonValue &value, files) {
            QString path = value.toObject().value("path").toString();
            QString sha = value.toObject().value("sha").toString();
            QString type = value.toObject().value("type").toString();

            if (type == "blob") {
                QString fileChecksum = value.toObject().value("sha").toString();

                if (path == filepath)
                    return fileChecksum;
                //qDebug() << "File name:" << path << ", Checksum:" << fileChecksum;
            }
        }

        return "";
    }


    void repoListFilesinDir(const QString& dirpath) {
        QNetworkRequest request(QUrl(QString("https://api.github.com/repos/") + username + QString("/") + reponame + QString("/contents/") + dirpath));
        request.setRawHeader("Authorization", (QString("Bearer ") + token).toUtf8());
        request.setRawHeader("Accept", "application/vnd.github.v3+json");

        QNetworkAccessManager manager;
        QNetworkReply *reply = manager.get(request);

        while (!reply->isFinished()) {
            QApplication::processEvents();
        }

        QByteArray response = reply->readAll();
        reply->deleteLater();

        QJsonDocument json = QJsonDocument::fromJson(response);
        QJsonArray files = json.array();

        foreach (const QJsonValue &value, files) {
            QString name = value.toObject().value("name").toString();
            QString type = value.toObject().value("type").toString();
            QString sha = value.toObject().value("sha").toString();
            QString downloadUrl = value.toObject().value("download_url").toString();
            qDebug() << "File:" << name << ", Type:" << type << ", Sha" << sha;
        }
    }

    // pobiera cały plik !!!!
    QString repoGetShaOfFile(const QString& filepath) {
        // Pobranie sumy kontrolnej pliku
        QNetworkRequest request(QUrl(QString("https://api.github.com/repos/") + username + QString("/") + reponame +
                                     QString("/contents/") + filepath));

        request.setRawHeader("Authorization", (QString("Bearer ") + token).toUtf8());
        QNetworkAccessManager manager;
        QNetworkReply *reply = manager.get(request);

        while (!reply->isFinished()) {
            QApplication::processEvents();
        }

        QByteArray response = reply->readAll();
        reply->deleteLater();

        QJsonDocument json = QJsonDocument::fromJson(response);
        QString checksum = json.object().value("sha").toString();
        return checksum;
    }

    QString getShaOfFile(const QString& filename) {
        QFile file1(filename);
        file1.open(QIODevice::ReadOnly);

        QByteArray content2 = QString("blob " + QString::number(file1.size())).toUtf8();// + file1.readAll();
        content2.append('\0');
        content2.append(file1.readAll());

        file1.close();

        QByteArray checksum2 = QCryptographicHash::hash(content2, QCryptographicHash::Sha1);
        return checksum2.toHex();
    }



private:
    QString username;
    QString reponame;
    QString token;


};

#endif


