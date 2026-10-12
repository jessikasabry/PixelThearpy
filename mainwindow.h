#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <functional>

class QLabel;
class QVBoxLayout;
class Image;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    void addFilters();
    void addFilterButton(const QString &text, std::function<void()> action);
    void run(std::function<void()> action);
    bool needImage();
    void showImage();
    void openImage();
    void saveImage();
    void undo();
    void sliderFilter(const QString &title, int minV, int maxV, int initV,
                      std::function<void(int)> apply, bool live = true);

    Ui::MainWindow *ui;
    QLabel *preview = nullptr;
    QVBoxLayout *buttonsLayout = nullptr;
    Image *currentImage = nullptr;
    Image *previousImage = nullptr;
};
#endif // MAINWINDOW_H
