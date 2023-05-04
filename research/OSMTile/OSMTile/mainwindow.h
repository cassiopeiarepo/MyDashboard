#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QPainter>

#include <QFile>
#include <QMouseEvent>
#include <cmath>

#include <QGridLayout>
#include <QPushButton>

class OSMWidget : public QWidget {
Q_OBJECT

public:

    class TileData {
    public:
        TileData(int _zoom, int _x, int _y) : zoom(_zoom), x(_x), y(_y) { }

        int zoom;
        int x;
        int y;
        QImage image;
    };



    OSMWidget(QWidget* parent, QNetworkAccessManager *_manager) : QWidget(parent), zoom(10),  manager(_manager), tile_w(256), tile_h(256), is_marker(false) {

        QGridLayout *gridLayout = new QGridLayout(this);

        QSpacerItem *horizontalSpacer = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Fixed);
        QSpacerItem *verticalSpacer = new QSpacerItem(1, 1, QSizePolicy::Fixed, QSizePolicy::Expanding);

        QVBoxLayout *buttonsLayout = new QVBoxLayout();
        QPushButton *button1 = new QPushButton("+");
        button1->setFixedSize(30,30);
        QObject::connect(button1, &QAbstractButton::pressed, this, &OSMWidget::onZoonInButtonPressed);

        QPushButton *button2 = new QPushButton("-");
        button2->setFixedSize(30,30);
        QObject::connect(button2, &QAbstractButton::pressed, this, &OSMWidget::onZoonOutButtonPressed);

        QSpacerItem *menuSpacer = new QSpacerItem(1, 1, QSizePolicy::Fixed, QSizePolicy::Expanding);
        buttonsLayout->addItem(menuSpacer);
        buttonsLayout->addWidget(button1);
        buttonsLayout->addWidget(button2);

        gridLayout->addItem(horizontalSpacer, 0, 0);
        gridLayout->addItem(verticalSpacer, 0, 1, 2, 1);
        gridLayout->addLayout(buttonsLayout, 1, 2);

        this->setLayout(gridLayout);


        marker_image.load(":/icons/location_on_FILL0_wght400_GRAD0_opsz48.png");
        setCenterZoomLatLon(10, 50.40747703301534, 18.86902404795005);
        setMarker(true, 50.40747703301534, 18.86902404795005);
    }

    void update_map() {

        int top_left_x, top_left_y, top_left_tile_x, top_left_tile_y, count_x, count_y;

        get_view_tiles(top_left_x, top_left_y, top_left_tile_x, top_left_tile_y, count_x, count_y);

        for (int j = 0; j < count_y; j++) {
            for (int i = 0; i < count_x; i++) {
                get_tile(zoom, top_left_tile_x + i, top_left_tile_y + j);
            }
        }
    }

    void get_view_tiles(int &top_left_x, int &top_left_y, int &top_left_tile_x, int &top_left_tile_y, int &count_x, int &count_y) {
        int w = width();
        int h = height();

        QPoint center(w/2, h/2);

        QPoint center_tile(center.x() - center_offset_x, center.y() - center_offset_y);

        top_left_x = center_tile.x();
        top_left_y = center_tile.y();

        top_left_tile_x = center_tile_x;
        top_left_tile_y = center_tile_y;

        while (top_left_x > 0) {
            top_left_x -= 256;
            top_left_tile_x -= 1;
        }

        while (top_left_y > 0) {
            top_left_y -= 256;
            top_left_tile_y -= 1;
        }

        count_x = (w - top_left_x) / tile_w + 1;
        count_y = (h - top_left_y) / tile_h + 1;
    }

    void get_tile(int t_zoom, int t_tile_x, int t_tile_y) {

        int tile_index = getTilesIndex(t_zoom, t_tile_x, t_tile_y);

        if (tile_index >= 0)
            return;

        int replay_index = getReprayIndex(t_zoom, t_tile_x, t_tile_y);
        if (replay_index >= 0 )
            return;

        //QString url = QString("https://a.tile.openstreetmap.org/%1/%2/%3.png").arg(t_zoom).arg(t_tile_x).arg(t_tile_y);
        QString url = QString("https://tile.openstreetmap.org/%1/%2/%3.png").arg(t_zoom).arg(t_tile_x).arg(t_tile_y);
        //QString url = QString("https://tile.opentopomap.org/%1/%2/%3.png").arg(t_zoom).arg(t_tile_x).arg(t_tile_y);

        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::UserAgentHeader, "MyDashboard/1.0 (mhersztowski@gmail.com)"); // Zmień na własny użytkownik-agenta i adres e-mail

        QNetworkReply *reply = manager->get(request);

        reply->setProperty("t_zoom", t_zoom);
        reply->setProperty("t_tile_x", t_tile_x);
        reply->setProperty("t_tile_y", t_tile_y);

        replays.append(reply);
        //QObject::connect(reply, &QNetworkReply::finished, this, &OSMWidget::handleFinished);

        QObject::connect(reply, &QNetworkReply::finished, [reply, this]() {

            replays.removeOne(reply);

            if (reply->error() != QNetworkReply::NoError) {
                qDebug() << "Error:" << reply->errorString();
            } else {

                //QImage image;
                //bool success = image.loadFromData(reply->readAll(), "PNG");
                //setImage(image);

                TileData tile(reply->property("t_zoom").toInt(), reply->property("t_tile_x").toInt(), reply->property("t_tile_y").toInt());
                tiles.append(tile);
                tiles.last().image.loadFromData(reply->readAll(), "PNG");
                update();

                //qDebug() << "Tile set";

                /*
                // Zapisz obraz kafelka do pliku
                QFile file("d:/tile.png");
                if (file.open(QIODevice::WriteOnly)) {
                    file.write(reply->readAll());
                    file.close();
                    qDebug() << "Tile saved to tile.png";
                } else {
                    qDebug() << "Error opening file for writing";
                }
                */
            }

            int status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            //qDebug() << "status_code:" << status_code;

            reply->deleteLater();
        });
    }

    void setImage(const QImage &image) {
        m_image = image;
        update(); // Wymuszenie przerysowania widgetu
    }

    void setMarker(bool visible, double lat, double lon) {
        is_marker = visible;
        marker_lat = lat;
        marker_lon = lon;
    }

    /*
    void latLonToTileXY(double lat, double lon, int zoom, int &tileX, int &tileY, double &offsetX, double &offsetY) {
        double latRad = lat * M_PI / 180.0;
        double n = pow(2.0, zoom);

        tileX = static_cast<int>((lon + 180.0) / 360.0 * n);
        tileY = static_cast<int>((1.0 - log(tan(latRad) + 1.0 / cos(latRad)) / M_PI) / 2.0 * n);

        double unitX = (lon + 180.0) / 360.0 * n - tileX;
        double unitY = (1.0 - log(tan(latRad) + 1.0 / cos(latRad)) / M_PI) / 2.0 * n - tileY;

        offsetX = unitX * 256; // 256 to rozmiar kafelka w pikselach
        offsetY = unitY * 256;
    }
    */

    void latLonToTileXY(double lat, double lon, int zoom, int &tileX, int &tileY, int &offsetX, int &offsetY) {
        double latRad = lat * M_PI / 180.0;
        double n = pow(2.0, zoom);

        tileX = static_cast<int>((lon + 180.0) / 360.0 * n);
        tileY = static_cast<int>((1.0 - log(tan(latRad) + 1.0 / cos(latRad)) / M_PI) / 2.0 * n);

        double unitX = (lon + 180.0) / 360.0 * n - tileX;
        double unitY = (1.0 - log(tan(latRad) + 1.0 / cos(latRad)) / M_PI) / 2.0 * n - tileY;

        offsetX = static_cast<int>(unitX * 256); // 256 to rozmiar kafelka w pikselach
        offsetY = static_cast<int>(unitY * 256);
    }

    void latLonToPoint(double lat, double lon, int zoom, int &pos_x, int &pos_y) {
        int tileX, tileY, offsetX, offsetY;

        latLonToTileXY(lat, lon, zoom, tileX, tileY, offsetX, offsetY);
        tileToPoint(tileX, tileY, offsetX, offsetY, pos_x, pos_y);
    }

    void tileToPoint(int tileX, int tileY, int offsetX, int offsetY, int &pos_x, int &pos_y) {

        /*
        int center_tile_x;
        int center_tile_y;
        int center_offset_x;
        int center_offset_y;
        */

        int top_left_x, top_left_y, top_left_tile_x, top_left_tile_y, count_x, count_y;

        get_view_tiles(top_left_x, top_left_y, top_left_tile_x, top_left_tile_y, count_x, count_y);


        int diff_tile_x = tileX - top_left_tile_x;
        int diff_tile_y = tileY - top_left_tile_y;

        pos_x = diff_tile_x * tile_w + offsetX + top_left_x;
        pos_y = diff_tile_y * tile_h + offsetY + top_left_y;

    }

    void pointToLatLon(QPoint point, double &lat, double &lon) {
        int tile_x, tile_y, offset_x, offset_y;

        pointToTile(point, tile_x, tile_y, offset_x, offset_y);

        lat =  tileToLatitude(tile_y, zoom, offset_y);
        lon =  tileToLongitude(tile_x, zoom, offset_x);
    }

    void pointToTile(QPoint point, int &tile_x, int &tile_y, int &offset_x, int &offset_y) {
        int top_left_x, top_left_y, top_left_tile_x, top_left_tile_y, count_x, count_y;

        get_view_tiles(top_left_x, top_left_y, top_left_tile_x, top_left_tile_y, count_x, count_y);

        int x = point.x() - top_left_x;
        int y = point.y() - top_left_y;

        int count_x2 = x / tile_w;
        int count_y2 = y / tile_h;

        tile_x = top_left_tile_x + count_x2;
        tile_y = top_left_tile_y + count_y2;

        offset_x = x - count_x2 * tile_w;
        offset_y = y - count_y2 * tile_h;
    }

    double tileToLatitude(int tileY, int zoom, int offsetY) {
        double n = pow(2, zoom);
        double lat_rad = atan(sinh(M_PI * (1 - 2 * (tileY + offsetY / 256.0) / n)));
        double lat_deg = lat_rad * 180.0 / M_PI;
        return lat_deg;
    }

    double tileToLongitude(int tileX, int zoom, int offsetX) {
        double n = pow(2, zoom);
        double lon_deg = (tileX + offsetX / 256.0) / n * 360.0 - 180.0;
        return lon_deg;
    }

public slots:

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);

        painter.setRenderHint(QPainter::Antialiasing, true); // Włącz antyaliasing
        painter.setRenderHint(QPainter::SmoothPixmapTransform, true); // Włącz wygładzanie transformacji pixmapy

        //qDebug() << "------------draw---------------";

        int top_left_x, top_left_y, top_left_tile_x, top_left_tile_y, count_x, count_y;

        get_view_tiles(top_left_x, top_left_y, top_left_tile_x, top_left_tile_y, count_x, count_y);

        int tile_y;

        for (int j = 0; j < count_y; j++) {
            tile_y = top_left_tile_y + j;

            for (int i = 0; i < count_x; i++) {
                //get_tile(zoom, top_left_tile_x + i, top_left_tile_y + j);
                int tile_x = top_left_tile_x + i;

                int tile_index = getTilesIndex(zoom, tile_x, tile_y);

                if (tile_index >= 0) {
                    QRectF rect(top_left_x + i * tile_w, top_left_y + j * tile_h, tiles[tile_index].image.width(), tiles[tile_index].image.height());
                    painter.drawImage(rect, tiles[tile_index].image);
                    //qDebug() << "draw " << tile_x << " " << tile_y;
                }
            }
        }

        if (is_marker) {
            int pos_x, pos_y;
            latLonToPoint(marker_lat, marker_lon, zoom, pos_x, pos_y);

            QRectF rect(pos_x - marker_image.width()/2, pos_y - marker_image.height(), marker_image.width(), marker_image.height());
            painter.drawImage(rect, marker_image);

            //marker_lat = lat;
            //marker_lon = lon;
        }
    }

    void mousePressEvent(QMouseEvent *event) override {
        QWidget::mousePressEvent(event);

        mousepress_tile_x = center_tile_x;
        mousepress_tile_y = center_tile_y;
        mousepress_offset_x = center_offset_x;
        mousepress_offset_y = center_offset_y;

        mousepress_pos = event->pos();
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        QWidget::mouseMoveEvent(event);

        //qDebug() << "mouse " << event->pos();

        QPoint diff =  mousepress_pos - event->pos();

        int x = mousepress_offset_x + diff.x();
        int y = mousepress_offset_y + diff.y();

        int tiles_count_x = x / tile_w;
        int tiles_count_y = y / tile_h;

        center_tile_x = mousepress_tile_x + tiles_count_x;
        center_tile_y = mousepress_tile_y + tiles_count_y;

        center_offset_x = x - tiles_count_x * tile_w;
        center_offset_y = y - tiles_count_y * tile_h;

        center_lat = tileToLatitude(center_tile_y, zoom, center_offset_y);
        center_lon = tileToLongitude(center_tile_x, zoom, center_offset_x);

        update_map();
        update();
    }

    void keyPressEvent(QKeyEvent *event) override {
        QWidget::keyPressEvent(event);

        if (event->key() == Qt::Key_Plus) {
            zoomIn();

        } else if (event->key() == Qt::Key_Minus) {
            zoomOut();
        }
    }

    void mouseDoubleClickEvent(QMouseEvent *event) override {
        QWidget::mouseDoubleClickEvent(event);

        zoomInPoint(event->pos());
    }

    void wheelEvent(QWheelEvent *event) override {
            int delta = event->angleDelta().y();
            QPoint point(event->position().x(), event->position().y());

            if (delta > 0) {
                zoomInPoint(point);
            } else {
                zoomOutPoint(point);
            }
        }

    void setCenterZoomLatLon(int _zoom, double _lat, double _lon) {
        zoom = _zoom;
        center_lat = _lat;
        center_lon = _lon;

        latLonToTileXY(center_lat, center_lon, zoom, center_tile_x, center_tile_y,  center_offset_x, center_offset_y);
    }



    void zoomIn() {
        //qDebug() << "zoomIn";
        zoom++;

        latLonToTileXY(center_lat, center_lon, zoom, center_tile_x, center_tile_y,  center_offset_x, center_offset_y);

        update_map();
        update();
    }

    void zoomOut() {

        if (zoom <= 0)
            return;

        //qDebug() << "zoomOut";

        zoom--;

        latLonToTileXY(center_lat, center_lon, zoom, center_tile_x, center_tile_y,  center_offset_x, center_offset_y);
        update_map();
        update();
    }

    void zoomInPoint(QPoint point) {
        zoomPoint(zoom + 1, point);
    }

    void zoomOutPoint(QPoint point) {
        zoomPoint(zoom - 1, point);
    }

    void zoomPoint(int _zoom, QPoint point) {
        double lat, lon;
        pointToLatLon(point, lat, lon);
        zoom = _zoom;

        int tile_x, tile_y,  offset_x, offset_y;

        latLonToTileXY(lat, lon, zoom, tile_x, tile_y,  offset_x, offset_y);

        int diff_x = width() / 2 - point.x();
        int diff_y = height() / 2 - point.y() ;

        int count_x = diff_x / tile_w;
        int count_y = diff_y / tile_h;

        center_tile_x = tile_x + count_x;
        center_tile_y = tile_y + count_y;

        center_offset_x = offset_x + diff_x - count_x * tile_w;
        center_offset_y = offset_y + diff_y - count_y * tile_h;

        if (center_offset_x < 0) {
            center_tile_x--;
            center_offset_x = tile_w + center_offset_x;
        } else if (center_offset_x > tile_w) {
            center_tile_x++;
            center_offset_x = center_offset_x - tile_w;
        }

        if (center_offset_y < 0) {
            center_tile_y--;
            center_offset_y = tile_h + center_offset_y;
        } else if (center_offset_y > tile_h) {
            center_tile_y++;
            center_offset_y = center_offset_y - tile_h;
        }

        center_lat = tileToLatitude(center_tile_y, zoom, center_offset_y);
        center_lon = tileToLongitude(center_tile_x, zoom, center_offset_x);

        update_map();
        update();
    }

public slots:
    void onZoonInButtonPressed() {
        zoomIn();
    }

    void onZoonOutButtonPressed() {
        zoomOut();
    }


private:
    int zoom;

    int center_tile_x;
    int center_tile_y;
    int center_offset_x;
    int center_offset_y;

    double center_lat;
    double center_lon;

    double marker_lat;
    double marker_lon;
    bool is_marker;
    QImage marker_image;

    int mousepress_tile_x;
    int mousepress_tile_y;
    int mousepress_offset_x;
    int mousepress_offset_y;

    QPoint mousepress_pos;

    int tile_w;
    int tile_h;

    QList<TileData> tiles;

    QNetworkAccessManager *manager;
    QList<QNetworkReply*> replays;

    QImage m_image;

    int getTilesIndex(int zoom, int tile_x, int tile_y) {
        for (int i = 0; i < tiles.size(); i++) {
            if (tiles[i].zoom == zoom && tiles[i].x == tile_x && tiles[i].y == tile_y) {
                return i;
            }
        }
        return -1;
    }

    int getReprayIndex(int zoom, int tile_x, int tile_y) {
        for (int i = 0; i < replays.size(); i++) {
            if (replays[i]->property("t_zoom").toInt() == zoom && replays[i]->property("t_tile_x").toInt() == tile_x && replays[i]->property("t_tile_y").toInt() == tile_y) {
                return i;
            }
        }
        return -1;
    }
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mouseMoveEvent(QMouseEvent *event) override {
        QMainWindow::mouseMoveEvent(event);

        //qDebug() << "mouse " << event->pos();

    }

    void resizeEvent(QResizeEvent *event) override {
        osm->update_map();;
    }

private:
    QNetworkAccessManager manager;
    OSMWidget* osm;
};
#endif // MAINWINDOW_H
