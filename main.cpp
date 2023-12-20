#include <QApplication>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLineEdit>
#include <QFormLayout>
#include <QDialog>
#include <QDialogButtonBox>

struct Service {
    QString name;
    QString specialist;
    double cost;
    QString time;
};

class ServiceListApp : public QWidget {
public:
    ServiceListApp(QWidget *parent = nullptr) : QWidget(parent) {
        // Создаем таблицу для отображения списка услуг
        tableWidget = new QTableWidget(this);
        tableWidget->setColumnCount(4);
        tableWidget->setHorizontalHeaderLabels({"Название услуги", "Специалист", "Цена услуги", "Время приема"});

        // Создаем кнопки для добавления и удаления услуг
        QPushButton *addButton = new QPushButton("Добавить услугу", this);
        QPushButton *removeButton = new QPushButton("Удалить услугу", this);

        // Создаем вертикальный лейаут и добавляем в него элементы
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(tableWidget);
        layout->addWidget(addButton);
        layout->addWidget(removeButton);

        // Подключаем сигналы кнопок к соответствующим слотам
        connect(addButton, &QPushButton::clicked, this, &ServiceListApp::addService);
        connect(removeButton, &QPushButton::clicked, this, &ServiceListApp::removeService);
        // Заполняем таблицу данными
        Service service1{"Консультация", "Иванов.А.В.", 100.0, "1 час"};
        Service service2{"Массаж ", "Киреева Д.Н.", 200.0, "1 час"};
        Service service3{"Сдача крови ", "Третьяков К.Н.", 50.0, "5 минут"};
        services.append(service1);
        services.append(service2);
        services.append(service3);
        updateTable();
        resize(500, 400);
    }

private slots:
    void addService() {
        // Создаем диалоговое окно для ввода данных о новой услуге
        QDialog dialog(this);
        QFormLayout formLayout(&dialog);

        QLineEdit *nameLineEdit = new QLineEdit(&dialog);
        QLineEdit *specialistLineEdit = new QLineEdit(&dialog);
        QLineEdit *costLineEdit = new QLineEdit(&dialog);
        QLineEdit *timeLineEdit = new QLineEdit(&dialog);

        formLayout.addRow("Название услуги:", nameLineEdit);
        formLayout.addRow("Наименование специалиста:", specialistLineEdit);
        formLayout.addRow("Стоимость услуги:", costLineEdit);
        formLayout.addRow("Время оказания услуги:", timeLineEdit);

        QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
        formLayout.addRow(&buttonBox);

        // Обработка нажатия кнопки "ОК"
        connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);

        // Обработка нажатия кнопки "Отмена"
        connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

        if (dialog.exec() == QDialog::Accepted) {
            // Получаем введенные пользователем данные
            QString name = nameLineEdit->text();
            QString specialist = specialistLineEdit->text();
            double cost = costLineEdit->text().toDouble();
            QString time = timeLineEdit->text();

        // Проверяем корректность данных
        if (name.isEmpty() || specialist.isEmpty() || cost == 0.0 || time.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Некорректные данные. Пожалуйста, заполните все поля корректно.");
            return;
            }

            // Создаем объект услуги и добавляем его в список
            Service service{name, specialist, cost, time};
            services.append(service);

            // Обновляем таблицу
            updateTable();
        }
    }

    void removeService() {
        // Получаем индекс выбранной строки в таблице
        int selectedRow = tableWidget->currentRow();


        if (selectedRow >= 0 && selectedRow < services.size()) {
            // Удаляем выбранную услугу из списка
            services.removeAt(selectedRow);

            // Обновляем таблицу
            updateTable();
        } else {
            QMessageBox::warning(this, "Ошибка", "Выберите услугу для удаления.");
        }
    }

    void updateTable() {
        // Очищаем таблицу
        tableWidget->clearContents();
        tableWidget->setRowCount(0);


        // Заполняем таблицу данными из списка услуг
        for (int i = 0; i < services.size(); ++i) {
            const Service& service = services.at(i);

            QTableWidgetItem *nameItem = new QTableWidgetItem(service.name);
            QTableWidgetItem *specialistItem = new QTableWidgetItem(service.specialist);
            QTableWidgetItem *costItem = new QTableWidgetItem(QString::number(service.cost));
            QTableWidgetItem *timeItem = new QTableWidgetItem(service.time);

            tableWidget->insertRow(i);
            tableWidget->setItem(i, 0, nameItem);
            tableWidget->setItem(i, 1, specialistItem);
            tableWidget->setItem(i, 2, costItem);
            tableWidget->setItem(i, 3, timeItem);
        }
    }

private:
    QTableWidget *tableWidget;
    QList<Service> services;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    ServiceListApp serviceListApp;
    serviceListApp.show();

    return app.exec();
}


