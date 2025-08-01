#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openFile();
    void updateImage();
    void prevFrame();
    void nextFrame();
    void requestUpdate();
    void jumpToFrame();
    void togglePlayback();
    void playNextFrame();

private:
    void createActions();
    void createMenus();
    void createSettingsPanel();
    void updateFrameNavigation();
    void closeCurrentImageFile();

    // YUV to RGB conversion helpers
    // YUV420SP (NV21): Y plane, then interleaved VU plane
    void nv21_to_rgb24(const uchar *yuv, uchar *rgb, int width, int height, int linesize);

    // YUV420SP (NV12): Y plane, then interleaved UV plane
    void nv12_to_rgb24(const uchar *yuv, uchar *rgb, int width, int height, int linesize);

    // YUV420P (YV12): Y plane, then V plane, then U plane
    void yv12_to_rgb24(const uchar *yuv, uchar *rgb, int width, int height, int linesize);

    // YUV420P (I420/YU12): Y plane, then U plane, then V plane
    void i420_to_rgb24(const uchar *yuv, uchar *rgb, int width, int height, int linesize);

    // YUV422P (I422)
    void i422_to_rgb24(const uchar *yuv, uchar *rgb, int width, int height, int linesize);

    // Image data
    QFile currentImageFile;
    uchar *mappedData;
    qint64 mappedDataSize;
    int currentFrame;
    int totalFrames;
    QImage *image;

    // Timers
    QTimer *updateTimer;
    QTimer *playbackTimer;

    // Main image display
    QLabel *imageLabel;

    // Settings Panel Widgets
    QSpinBox *widthSpinBox;
    QSpinBox *heightSpinBox;
    QComboBox *pixelFormatComboBox;
    QSpinBox *linesizeSpinBox;
    QPushButton *prevFrameButton;
    QPushButton *nextFrameButton;
    QLabel *currentFrameLabel;
    QSpinBox *frameSpinBox;
    QPushButton *jumpButton;
    QSpinBox *fpsSpinBox;
    QPushButton *playButton;

    // Actions and Menus
    QAction *openAction;
    QMenu *fileMenu;
};

#endif // MAINWINDOW_H
