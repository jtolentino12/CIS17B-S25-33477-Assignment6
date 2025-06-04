#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    auto *central = new QWidget;
    auto *layout = new QVBoxLayout(central);

    // Input fields
    idInput = new QLineEdit; idInput->setPlaceholderText("ID");
    descInput = new QLineEdit; descInput->setPlaceholderText("Description");
    locInput = new QLineEdit; locInput->setPlaceholderText("Location");
    QPushButton *addBtn = new QPushButton("Add Item");

    findIdInput = new QLineEdit; findIdInput->setPlaceholderText("Find by ID");
    QPushButton *findBtn = new QPushButton("Find");

    removeIdInput = new QLineEdit; removeIdInput->setPlaceholderText("Remove by ID");
    QPushButton *removeBtn = new QPushButton("Remove");

    itemList = new QListWidget;

    // Add to layout
    layout->addWidget(idInput);
    layout->addWidget(descInput);
    layout->addWidget(locInput);
    layout->addWidget(addBtn);
    layout->addWidget(findIdInput);
    layout->addWidget(findBtn);
    layout->addWidget(removeIdInput);
    layout->addWidget(removeBtn);
    layout->addWidget(itemList);

    setCentralWidget(central);

    // Menu bar
    QMenu *fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction("Exit", this, &QMainWindow::close);
    QMenu *helpMenu = menuBar()->addMenu("Help");
    helpMenu->addAction("About", this, &MainWindow::showAboutDialog);

    // Connect signals
    connect(addBtn, &QPushButton::clicked, this, &MainWindow::onAddItemClicked);
    connect(findBtn, &QPushButton::clicked, this, &MainWindow::onFindItemClicked);
    connect(removeBtn, &QPushButton::clicked, this, &MainWindow::onRemoveItemClicked);
}

MainWindow::~MainWindow() = default;

void MainWindow::onAddItemClicked() {
    try {
        auto item = std::make_shared<StoredItem>(idInput->text().toStdString(),
                                                 descInput->text().toStdString(),
                                                 locInput->text().toStdString());
        manager.addItem(item);
        itemList->clear();
        for (const auto& i : manager.listItemsByDescription()) {
            itemList->addItem(QString::fromStdString("ID: " + i->getId() +
                                                     ", Description: " + i->getDescription() +
                                                     ", Location: " + i->getLocation()));
        }
    } catch (const DuplicateItemException& e) {
        QMessageBox::warning(this, "Duplicate", e.what());
    }
}

void MainWindow::onFindItemClicked() {
    try {
        auto item = manager.findById(findIdInput->text().toStdString());
        QMessageBox::information(this, "Item Found",
                                 QString::fromStdString("Description: " + item->getDescription() + "\nLocation: " + item->getLocation()));
    } catch (const ItemNotFoundException& e) {
        QMessageBox::warning(this, "Not Found", e.what());
    }
}

void MainWindow::onRemoveItemClicked() {
    try {
        manager.removeItem(removeIdInput->text().toStdString());
        itemList->clear();
        for (const auto& i : manager.listItemsByDescription()) {
            itemList->addItem(QString::fromStdString("ID: " + i->getId() +
                                                     ", Description: " + i->getDescription() +
                                                     ", Location: " + i->getLocation()));
        }
    } catch (const ItemNotFoundException& e) {
        QMessageBox::warning(this, "Not Found", e.what());
    }
}

void MainWindow::showAboutDialog() {
    QMessageBox::about(this, "About", "Jericho Tolentino\nCIS17B Assignment6");
}
