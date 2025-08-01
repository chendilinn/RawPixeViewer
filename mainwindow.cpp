#include "mainwindow.h"

// YUV to RGB conversion helpers
static inline int clamp(int value) {
    if (value < 0) return 0;
    if (value > 255) return 255;
    return value;
}

// YUV420P (I420/YU12): Y plane, then U plane, then V plane
void MainWindow::i420_to_rgb24(const uchar *yuv, uchar *rgb, int width, int height, int linesize)
{
    const uchar *y_plane = yuv;
    const uchar *u_plane = yuv + linesize * height;
    const uchar *v_plane = u_plane + (linesize / 2) * (height / 2);
    int uv_linesize = linesize / 2;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int y = y_plane[i * linesize + j];
            int u = u_plane[(i / 2) * uv_linesize + (j / 2)];
            int v = v_plane[(i / 2) * uv_linesize + (j / 2)];
            int c = y - 16;
            int d = u - 128;
            int e = v - 128;
            int r = clamp((298 * c + 409 * e + 128) >> 8);
            int g = clamp((298 * c - 100 * d - 208 * e + 128) >> 8);
            int b = clamp((298 * c + 516 * d + 128) >> 8);
            int rgb_index = (i * width + j) * 3;
            rgb[rgb_index] = r;
            rgb[rgb_index + 1] = g;
            rgb[rgb_index + 2] = b;
        }
    }
}

// YUV420P (YV12): Y plane, then V plane, then U plane
void MainWindow::yv12_to_rgb24(const uchar *yuv, uchar *rgb, int width, int height, int linesize)
{
    const uchar *y_plane = yuv;
    const uchar *v_plane = yuv + linesize * height;
    const uchar *u_plane = v_plane + (linesize / 2) * (height / 2);
    int uv_linesize = linesize / 2;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int y = y_plane[i * linesize + j];
            int u = u_plane[(i / 2) * uv_linesize + (j / 2)];
            int v = v_plane[(i / 2) * uv_linesize + (j / 2)];
            int c = y - 16;
            int d = u - 128;
            int e = v - 128;
            int r = clamp((298 * c + 409 * e + 128) >> 8);
            int g = clamp((298 * c - 100 * d - 208 * e + 128) >> 8);
            int b = clamp((298 * c + 516 * d + 128) >> 8);
            int rgb_index = (i * width + j) * 3;
            rgb[rgb_index] = r;
            rgb[rgb_index + 1] = g;
            rgb[rgb_index + 2] = b;
        }
    }
}

// YUV420SP (NV12): Y plane, then interleaved UV plane
void MainWindow::nv12_to_rgb24(const uchar *yuv, uchar *rgb, int width, int height, int linesize)
{
    const uchar *y_plane = yuv;
    const uchar *uv_plane = yuv + linesize * height;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int y = y_plane[i * linesize + j];
            int u = uv_plane[(i / 2) * linesize + (j / 2) * 2];
            int v = uv_plane[(i / 2) * linesize + (j / 2) * 2 + 1];
            int c = y - 16;
            int d = u - 128;
            int e = v - 128;
            int r = clamp((298 * c + 409 * e + 128) >> 8);
            int g = clamp((298 * c - 100 * d - 208 * e + 128) >> 8);
            int b = clamp((298 * c + 516 * d + 128) >> 8);
            int rgb_index = (i * width + j) * 3;
            rgb[rgb_index] = r;
            rgb[rgb_index + 1] = g;
            rgb[rgb_index + 2] = b;
        }
    }
}

// YUV420SP (NV21): Y plane, then interleaved VU plane
void MainWindow::nv21_to_rgb24(const uchar *yuv, uchar *rgb, int width, int height, int linesize)
{
    const uchar *y_plane = yuv;
    const uchar *vu_plane = yuv + linesize * height;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int y = y_plane[i * linesize + j];
            int v = vu_plane[(i / 2) * linesize + (j / 2) * 2];
            int u = vu_plane[(i / 2) * linesize + (j / 2) * 2 + 1];
            int c = y - 16;
            int d = u - 128;
            int e = v - 128;
            int r = clamp((298 * c + 409 * e + 128) >> 8);
            int g = clamp((298 * c - 100 * d - 208 * e + 128) >> 8);
            int b = clamp((298 * c + 516 * d + 128) >> 8);
            int rgb_index = (i * width + j) * 3;
            rgb[rgb_index] = r;
            rgb[rgb_index + 1] = g;
            rgb[rgb_index + 2] = b;
        }
    }
}

// YUV422P (I422)
void MainWindow::i422_to_rgb24(const uchar *yuv, uchar *rgb, int width, int height, int linesize)
{
    const uchar *y_plane = yuv;
    const uchar *u_plane = yuv + linesize * height;
    const uchar *v_plane = u_plane + (linesize / 2) * height;
    int uv_linesize = linesize / 2;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int y = y_plane[i * linesize + j];
            int u = u_plane[i * uv_linesize + (j / 2)];
            int v = v_plane[i * uv_linesize + (j / 2)];
            int c = y - 16;
            int d = u - 128;
            int e = v - 128;
            int r = clamp((298 * c + 409 * e + 128) >> 8);
            int g = clamp((298 * c - 100 * d - 208 * e + 128) >> 8);
            int b = clamp((298 * c + 516 * d + 128) >> 8);
            int rgb_index = (i * width + j) * 3;
            rgb[rgb_index] = r;
            rgb[rgb_index + 1] = g;
            rgb[rgb_index + 2] = b;
        }
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), mappedData(nullptr), mappedDataSize(0), currentFrame(0), totalFrames(0), image(nullptr)
{
    // Central widget for image display
    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);
    setCentralWidget(imageLabel);

    createActions();
    createMenus();
    createSettingsPanel();

    // Debouncing timer for UI updates
    updateTimer = new QTimer(this);
    updateTimer->setSingleShot(true);
    updateTimer->setInterval(250); // 250ms delay
    connect(updateTimer, &QTimer::timeout, this, &MainWindow::updateImage);

    // Playback timer
    playbackTimer = new QTimer(this);
    connect(playbackTimer, &QTimer::timeout, this, &MainWindow::playNextFrame);

    setWindowTitle(tr("Raw Pixel Viewer"));
    resize(800, 600);
}

MainWindow::~MainWindow()
{
    closeCurrentImageFile();
    delete image;
}

void MainWindow::closeCurrentImageFile()
{
    playbackTimer->stop();
    if (mappedData) {
        currentImageFile.unmap(mappedData);
        mappedData = nullptr;
        mappedDataSize = 0;
    }
    if (currentImageFile.isOpen()) {
        currentImageFile.close();
    }
}

void MainWindow::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Image File"), "", tr("All Files (*.*);;YUV Files (*.yuv);;RGB Files (*.rgb)"));
    if (filePath.isEmpty()) {
        return;
    }

    closeCurrentImageFile(); // Close any previously opened file

    currentImageFile.setFileName(filePath);
    if (!currentImageFile.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Error"), tr("Could not open file."));
        return;
    }

    mappedDataSize = currentImageFile.size();
    if (mappedDataSize == 0) {
        QMessageBox::information(this, tr("Info"), tr("File is empty."));
        closeCurrentImageFile();
        return;
    }

    mappedData = currentImageFile.map(0, mappedDataSize);
    if (!mappedData) {
        QMessageBox::warning(this, tr("Error"), tr("Could not map file to memory."));
        closeCurrentImageFile();
        return;
    }

    currentFrame = 0;
    updateImage();
}

void MainWindow::updateImage()
{
    if (!mappedData) {
        return;
    }

    int width = widthSpinBox->value();
    int height = heightSpinBox->value();
    QString format = pixelFormatComboBox->currentText();
    int linesize = linesizeSpinBox->value();

    int frameSize = 0;
    if (format.startsWith("YUV420")) {
        frameSize = linesize * height * 3 / 2;
    } else if (format.startsWith("YUV422")) {
        frameSize = linesize * height * 2;
    } else if (format == "RGB888") {
        frameSize = linesize * height * 3;
    } else if (format == "RGBA8888") {
        frameSize = linesize * height * 4; // RGBX is 4 bytes per pixel, linesize is in bytes
    }

    if (frameSize <= 0) {
        QMessageBox::warning(this, tr("Error"), tr("Invalid format or parameters."));
        return;
    }

    totalFrames = mappedDataSize / frameSize;
    if (totalFrames == 0) {
        imageLabel->clear();
        imageLabel->setText(tr("No valid frames found. Check parameters."));
        return;
    }

    if (currentFrame >= totalFrames) {
        currentFrame = totalFrames - 1;
    }

    int frameOffset = currentFrame * frameSize;
    const uchar *frameData = mappedData + frameOffset;

    QImage *newImage = nullptr;

    if (format == "YUV420P (I420/YU12)") {
        newImage = new QImage(width, height, QImage::Format_RGB888);
        i420_to_rgb24(frameData, newImage->bits(), width, height, linesize);
    } else if (format == "YUV420P (YV12)") {
        newImage = new QImage(width, height, QImage::Format_RGB888);
        yv12_to_rgb24(frameData, newImage->bits(), width, height, linesize);
    } else if (format == "YUV420SP (NV12)") {
        newImage = new QImage(width, height, QImage::Format_RGB888);
        nv12_to_rgb24(frameData, newImage->bits(), width, height, linesize);
    } else if (format == "YUV420SP (NV21)") {
        newImage = new QImage(width, height, QImage::Format_RGB888);
        nv21_to_rgb24(frameData, newImage->bits(), width, height, linesize);
    } else if (format == "YUV422P (I422)") {
        newImage = new QImage(width, height, QImage::Format_RGB888);
        i422_to_rgb24(frameData, newImage->bits(), width, height, linesize);
    } else if (format == "RGB888") {
        newImage = new QImage(width, height, QImage::Format_RGB888);
        int copy_size = width*height*3;
        if((mappedDataSize - frameOffset) < width*height*3)
            copy_size = mappedDataSize - frameOffset;
        memcpy(newImage->bits(), frameData, copy_size);
    } else if (format == "RGBA8888") {
        newImage = new QImage(width, height, QImage::Format_RGBA8888);
        int copy_size = width*height*4;
        if((mappedDataSize - frameOffset) < width*height*4)
            copy_size = mappedDataSize - frameOffset;
        memcpy(newImage->bits(), frameData, copy_size);
    }

    if (newImage && !newImage->isNull()) {
        delete image; // Delete the old image
        image = newImage; // Assign the new one
        imageLabel->setPixmap(QPixmap::fromImage(*image));
    } else {
        delete newImage; // Clean up if image creation failed
    }

    updateFrameNavigation();
}

void MainWindow::requestUpdate()
{
    updateTimer->start();
}

void MainWindow::togglePlayback()
{
    if (playbackTimer->isActive()) {
        playbackTimer->stop();
        playButton->setText(tr("Play"));
    } else {
        if (totalFrames > 1) {
            int fps = fpsSpinBox->value();
            if (fps > 0) {
                playbackTimer->start(1000 / fps);
                playButton->setText(tr("Pause"));
            }
        }
    }
    updateFrameNavigation();
}

void MainWindow::playNextFrame()
{
    if (currentFrame < totalFrames - 1) {
        currentFrame++;
        updateImage();
    } else {
        // Stop at the last frame
        playbackTimer->stop();
        playButton->setText(tr("Play"));
        updateFrameNavigation();
    }
}

void MainWindow::jumpToFrame()
{
    if (totalFrames > 0) {
        int frame = frameSpinBox->value() - 1; // Convert 1-based to 0-based index
        if (frame >= 0 && frame < totalFrames) {
            currentFrame = frame;
            updateImage();
        }
    }
}

void MainWindow::prevFrame()
{
    if (currentFrame > 0) {
        currentFrame--;
        updateImage();
    }
}

void MainWindow::nextFrame()
{
    if (currentFrame < totalFrames - 1) {
        currentFrame++;
        updateImage();
    }
}

void MainWindow::createActions()
{
    openAction = new QAction(tr("&Open..."), this);
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
}

void MainWindow::createSettingsPanel()
{
    QDockWidget *dockWidget = new QDockWidget(tr("Settings"), this);
    addDockWidget(Qt::RightDockWidgetArea, dockWidget);

    QWidget *settingsWidget = new QWidget;
    QFormLayout *formLayout = new QFormLayout(settingsWidget);

    // Resolution
    widthSpinBox = new QSpinBox;
    widthSpinBox->setRange(1, 8192);
    widthSpinBox->setValue(1920);
    heightSpinBox = new QSpinBox;
    heightSpinBox->setRange(1, 8192);
    heightSpinBox->setValue(1080);
    QHBoxLayout *resolutionLayout = new QHBoxLayout;
    resolutionLayout->addWidget(widthSpinBox);
    resolutionLayout->addWidget(new QLabel(tr("x")));
    resolutionLayout->addWidget(heightSpinBox);
    formLayout->addRow(tr("Resolution:"), resolutionLayout);

    // Pixel Format
    pixelFormatComboBox = new QComboBox;
    pixelFormatComboBox->addItem("YUV420P (I420/YU12)");
    pixelFormatComboBox->addItem("YUV420P (YV12)");
    pixelFormatComboBox->addItem("YUV420SP (NV12)");
    pixelFormatComboBox->addItem("YUV420SP (NV21)");
    pixelFormatComboBox->addItem("YUV422P (I422)");
    pixelFormatComboBox->addItem("RGB888");
    pixelFormatComboBox->addItem("RGBA8888");
    formLayout->addRow(tr("Pixel Format:"), pixelFormatComboBox);

    // Linesize
    linesizeSpinBox = new QSpinBox;
    linesizeSpinBox->setRange(1, 16384);
    linesizeSpinBox->setValue(1920);
    formLayout->addRow(tr("Linesize:"), linesizeSpinBox);

    // Frame Navigation
    prevFrameButton = new QPushButton(tr("Previous Frame"));
    nextFrameButton = new QPushButton(tr("Next Frame"));
    currentFrameLabel = new QLabel(tr("Frame: 0 / 0"));
    currentFrameLabel->setAlignment(Qt::AlignCenter);
    QHBoxLayout *frameLayout = new QHBoxLayout;
    frameLayout->addWidget(prevFrameButton);
    frameLayout->addWidget(nextFrameButton);
    formLayout->addRow(frameLayout);
    formLayout->addRow(currentFrameLabel);

    // Jump to Frame
    frameSpinBox = new QSpinBox;
    frameSpinBox->setRange(1, 1); // Will be updated dynamically
    jumpButton = new QPushButton(tr("Jump"));
    QHBoxLayout *jumpLayout = new QHBoxLayout;
    jumpLayout->addWidget(new QLabel(tr("Go to Frame:")));
    jumpLayout->addWidget(frameSpinBox);
    jumpLayout->addWidget(jumpButton);
    formLayout->addRow(jumpLayout);

    // Playback
    fpsSpinBox = new QSpinBox;
    fpsSpinBox->setRange(1, 120);
    fpsSpinBox->setValue(30);
    playButton = new QPushButton(tr("Play"));
    QHBoxLayout *playbackLayout = new QHBoxLayout;
    playbackLayout->addWidget(new QLabel(tr("FPS:")));
    playbackLayout->addWidget(fpsSpinBox);
    playbackLayout->addWidget(playButton);
    formLayout->addRow(playbackLayout);

    dockWidget->setWidget(settingsWidget);

    // Connect signals
    connect(widthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::requestUpdate);
    connect(heightSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::requestUpdate);
    connect(pixelFormatComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::requestUpdate);
    connect(linesizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::requestUpdate);
    connect(prevFrameButton, &QPushButton::clicked, this, &MainWindow::prevFrame);
    connect(nextFrameButton, &QPushButton::clicked, this, &MainWindow::nextFrame);
    connect(jumpButton, &QPushButton::clicked, this, &MainWindow::jumpToFrame);
    connect(playButton, &QPushButton::clicked, this, &MainWindow::togglePlayback);
}

void MainWindow::updateFrameNavigation()
{
    bool isPlaying = playbackTimer->isActive();

    if (totalFrames > 0) {
        currentFrameLabel->setText(QString("Frame: %1 / %2").arg(currentFrame + 1).arg(totalFrames));
        frameSpinBox->setRange(1, totalFrames);
        frameSpinBox->setValue(currentFrame + 1);
    }
    else {
        currentFrameLabel->setText(tr("Frame: 0 / 0"));
        frameSpinBox->setRange(1, 1);
        frameSpinBox->setValue(1);
    }
    prevFrameButton->setEnabled(!isPlaying && currentFrame > 0);
    nextFrameButton->setEnabled(!isPlaying && currentFrame < totalFrames - 1);
    jumpButton->setEnabled(!isPlaying && totalFrames > 1);
    frameSpinBox->setEnabled(!isPlaying && totalFrames > 1);
    playButton->setEnabled(totalFrames > 1);
    fpsSpinBox->setEnabled(!isPlaying);

    if (isPlaying) {
        playButton->setText(tr("Pause"));
    } else {
        playButton->setText(tr("Play"));
    }
}
