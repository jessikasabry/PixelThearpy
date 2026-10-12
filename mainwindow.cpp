#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QStringList>
#include <QImage>
#include <QPixmap>
#include <QSlider>               // NEW
#include <QDialog>               // NEW
#include <QDialogButtonBox>      // NEW
#include <memory>

#include "Filters.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("BabyPhotoshop");
    resize(1000, 700);

    QWidget *central = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(central);

    QScrollArea *scroll = new QScrollArea;
    QWidget *panel = new QWidget;
    buttonsLayout = new QVBoxLayout(panel);
    scroll->setWidget(panel);
    scroll->setWidgetResizable(true);
    scroll->setFixedWidth(240);

    preview = new QLabel("Open an image to start");
    preview->setAlignment(Qt::AlignCenter);

    mainLayout->addWidget(scroll);
    mainLayout->addWidget(preview, 1);
    setCentralWidget(central);

    addFilterButton("Open image", [this]{ openImage(); });
    addFilterButton("Save image", [this]{ saveImage(); });
    addFilterButton("Undo", [this]{ undo(); });
    addFilters();
    buttonsLayout->addStretch();
}

MainWindow::~MainWindow()
{
    delete currentImage;
    delete previousImage;
    delete ui;
}

void MainWindow::addFilterButton(const QString &text, std::function<void()> action)
{
    QPushButton *b = new QPushButton(text);
    buttonsLayout->addWidget(b);
    connect(b, &QPushButton::clicked, this, [action]{ action(); });
}

bool MainWindow::needImage()
{
    if (!currentImage) {
        QMessageBox::information(this, "BabyPhotoshop", "Please open an image first.");
        return false;
    }
    return true;
}

void MainWindow::run(std::function<void()> action)
{
    if (!needImage()) return;
    delete previousImage;
    previousImage = new Image(*currentImage);
    try {
        action();
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
    showImage();
}

// CHANGED: faster, builds QImage directly from the pixel buffer
void MainWindow::showImage()
{
    if (!currentImage) return;
    QImage q(currentImage->imageData, currentImage->width, currentImage->height,
             currentImage->width * 3, QImage::Format_RGB888);
    preview->setPixmap(QPixmap::fromImage(q).scaled(750, 650, Qt::KeepAspectRatio,
                                                    Qt::SmoothTransformation));
}

void MainWindow::openImage()
{
    QString f = QFileDialog::getOpenFileName(this, "Open image", "",
                                             "Images (*.png *.jpg *.jpeg *.bmp *.tga)");
    if (f.isEmpty()) return;
    try {
        Image *img = new Image(f.toStdString());
        delete currentImage;
        currentImage = img;
        delete previousImage;
        previousImage = nullptr;
        showImage();
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void MainWindow::saveImage()
{
    if (!needImage()) return;
    QString f = QFileDialog::getSaveFileName(this, "Save image", "result.png",
                                             "Images (*.png *.jpg *.jpeg *.bmp *.tga)");
    if (f.isEmpty()) return;
    if (!f.contains('.')) f += ".png";
    try {
        currentImage->saveImage(f.toStdString());
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void MainWindow::undo()
{
    if (!previousImage) {
        QMessageBox::information(this, "BabyPhotoshop", "Nothing to undo.");
        return;
    }
    std::swap(currentImage, previousImage);
    showImage();
}

// NEW: dialog with a slider and live preview
void MainWindow::sliderFilter(const QString &title, int minV, int maxV, int initV,
                              std::function<void(int)> apply, bool live)
{
    if (!needImage()) return;

    Image original(*currentImage);              // the original: we restore it on every move

    QDialog dlg(this);
    dlg.setWindowTitle(title);
    QVBoxLayout *lay = new QVBoxLayout(&dlg);

    QLabel *valueLabel = new QLabel(QString::number(initV));
    valueLabel->setAlignment(Qt::AlignCenter);
    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(minV, maxV);
    slider->setValue(initV);
    slider->setTracking(live);                  // false = preview only when the slider is released
    QDialogButtonBox *box =
        new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    lay->addWidget(valueLabel);
    lay->addWidget(slider);
    lay->addWidget(box);

    connect(slider, &QSlider::sliderMoved, &dlg,
            [valueLabel](int v){ valueLabel->setText(QString::number(v)); });
    connect(slider, &QSlider::valueChanged, &dlg, [&](int v){
        valueLabel->setText(QString::number(v));
        *currentImage = original;               // always start from the original
        try { apply(v); } catch (...) {}
        showImage();
    });
    connect(box, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    connect(box, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);

    if (dlg.exec() == QDialog::Accepted) {
        delete previousImage;
        previousImage = new Image(original);    // Undo goes back to the original
        *currentImage = original;
        try { apply(slider->value()); }
        catch (const std::exception &e) { QMessageBox::critical(this, "Error", e.what()); }
    } else {
        *currentImage = original;               // Cancel
    }
    showImage();
}

void MainWindow::addFilters()
{
    addFilterButton("1. Grayscale", [this]{ run([this]{ turn_to_gray(*currentImage); }); });
    addFilterButton("2. Black and White", [this]{ run([this]{ BlackAndWhite(*currentImage); }); });
    addFilterButton("3. Invert", [this]{ run([this]{ invertImage(*currentImage); }); });

    addFilterButton("4. Frame", [this]{
        if (!needImage()) return;
        QStringList styles = {"Simple frame", "Fancy frame"};
        bool ok;
        QString s = QInputDialog::getItem(this, "Frame", "Style:", styles, 0, false, &ok);
        if (!ok) return;
        int size = QInputDialog::getInt(this, "Frame", "Frame size (pixels):", 10, 1, 200, 1, &ok);
        if (!ok) return;
        int choice = (s == styles[0]) ? 1 : 2;
        run([this, size, choice]{ ::applyframe(*currentImage, size, choice); });
    });

    addFilterButton("5. Flip", [this]{
        if (!needImage()) return;
        QStringList opts = {"Left-Right", "Top-Bottom"};
        bool ok;
        QString s = QInputDialog::getItem(this, "Flip", "Direction:", opts, 0, false, &ok);
        if (!ok) return;
        bool lr = (s == opts[0]);
        run([this, lr]{
            if (lr) flip_right_to_left(*currentImage);
            else flip_top_to_bottom(*currentImage);
        });
    });

    addFilterButton("6. Rotate", [this]{
        if (!needImage()) return;
        QStringList opts = {"90", "180", "270"};
        bool ok;
        QString s = QInputDialog::getItem(this, "Rotate", "Angle (clockwise):", opts, 0, false, &ok);
        if (!ok) return;
        int angle = s.toInt();
        run([this, angle]{ ::rotate(*currentImage, angle); });
    });

    // CHANGED: now uses the slider
    addFilterButton("7. Darken / Lighten", [this]{
        if (!needImage()) return;
        QStringList opts = {"Darken", "Lighten"};
        bool ok;
        QString s = QInputDialog::getItem(this, "Brightness", "Mode:", opts, 0, false, &ok);
        if (!ok) return;
        int choice = (s == opts[0]) ? 1 : 2;
        sliderFilter("Brightness level (%)", 0, 100, 50, [this, choice](int level){
            Darken_Lighten(*currentImage, level, choice);
        });
    });

    addFilterButton("8. Resize", [this]{
        if (!needImage()) return;
        bool ok;
        int w = QInputDialog::getInt(this, "Resize", "New width:", currentImage->width, 1, 10000, 1, &ok);
        if (!ok) return;
        int h = QInputDialog::getInt(this, "Resize", "New height:", currentImage->height, 1, 10000, 1, &ok);
        if (!ok) return;
        run([this, w, h]{ ::resize(*currentImage, w, h); });
    });

    addFilterButton("9. Merge", [this]{
        if (!needImage()) return;
        QString f = QFileDialog::getOpenFileName(this, "Second image", "",
                                                 "Images (*.png *.jpg *.jpeg *.bmp *.tga)");
        if (f.isEmpty()) return;
        std::shared_ptr<Image> other;
        try {
            other = std::make_shared<Image>(f.toStdString());
        } catch (const std::exception &e) {
            QMessageBox::critical(this, "Error", e.what());
            return;
        }
        int choice = 1;
        if (other->width != currentImage->width || other->height != currentImage->height) {
            QStringList opts = {"Resize to biggest size", "Merge common area"};
            bool ok;
            QString s = QInputDialog::getItem(this, "Merge", "Sizes differ:", opts, 0, false, &ok);
            if (!ok) return;
            choice = (s == opts[0]) ? 1 : 2;
        }
        run([this, other, choice]{ merge_images(*currentImage, *other, choice); });
    });

    addFilterButton("10. Detect Edges", [this]{ run([this]{ DetectedEdge(*currentImage); }); });

    addFilterButton("11. Crop", [this]{
        if (!needImage()) return;
        bool ok;
        int x = QInputDialog::getInt(this, "Crop", "Start X:", 0, 0, currentImage->width - 1, 1, &ok);
        if (!ok) return;
        int y = QInputDialog::getInt(this, "Crop", "Start Y:", 0, 0, currentImage->height - 1, 1, &ok);
        if (!ok) return;
        int w = QInputDialog::getInt(this, "Crop", "Width:", currentImage->width - x, 1, currentImage->width - x, 1, &ok);
        if (!ok) return;
        int h = QInputDialog::getInt(this, "Crop", "Height:", currentImage->height - y, 1, currentImage->height - y, 1, &ok);
        if (!ok) return;
        run([this, x, y, w, h]{
            Image cropped = cropImage(*currentImage, x, y, w, h);
            *currentImage = cropped;
        });
    });

    // CHANGED: now uses the slider (live = false because blur is heavy)
    addFilterButton("12. Blur", [this]{
        sliderFilter("Blur strength", 1, 20, 5, [this](int r){
            blur(*currentImage, r);
        }, false);
    });

    addFilterButton("13. Sunlight", [this]{ run([this]{ increase_brightness(*currentImage); }); });
    addFilterButton("14. Old TV", [this]{ run([this]{ OldTV(*currentImage); }); });
    addFilterButton("15. Purple", [this]{ run([this]{ purpleEffect(*currentImage); }); });
    addFilterButton("16. Infrared", [this]{ run([this]{ Samurai(*currentImage); }); });

    addFilterButton("17. Skew", [this]{
        if (!needImage()) return;
        bool ok;
        int a = QInputDialog::getInt(this, "Skew", "Angle (1-80):", 40, 1, 80, 1, &ok);
        if (!ok) return;
        run([this, a]{ skweness(*currentImage, a); });
    });

    addFilterButton("18. Oil Painting", [this]{ run([this]{ oilPainting(*currentImage); }); });
}