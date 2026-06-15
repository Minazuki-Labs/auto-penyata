#include "header/blockmanager.h"

#include <QScrollArea>
#include <QVBoxLayout>

BlockManager::BlockManager(QObject *parent)
    : QFrame(static_cast<QWidget*>(parent))
{
}

// Creates visual blocks for each item in the variant map from Json
void BlockManager::createAccountBlocks(const QVariantMap &variantMap, QStringList desiredOrder,
                                       Ui::MainWindow *m_ui, QScrollArea *scrollArea, QWidget *contentWidget)
{
    if (!scrollArea) {
        qCritical() << "Error: QScrollArea not found in UI file.";
        return;
    }

    // Clear the list of input fields and their initial values before creating new ones
    m_accountValueInputs.clear(); 

    // Check if the content widget exists and has a layout. If not, create a new layout
    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout*>(contentWidget->layout());
    if (!mainLayout) {
        mainLayout = new QVBoxLayout(contentWidget);
        mainLayout->setSpacing(10);
        mainLayout->setAlignment(Qt::AlignTop);
    } else {
        // Clear existing widgets in the layout before adding new ones
        QLayoutItem *item;
        while ((item = mainLayout->takeAt(0)) != nullptr) {
            if (item->widget()) {
                item->widget()->deleteLater();
            }
            delete item;
        }
    }

    QSet<QString> processedKeys;
    for (const QString &key : desiredOrder)
    {
        processedKeys.insert(key);
        double doubleValue = 0.00; // Default value

        if (variantMap.contains(key))
        {
            const QVariant value = variantMap.value(key);
            
            // Check if it can be converted to a double
            bool ok = false;
            double parsedValue = value.toDouble(&ok);
            if (ok) {
                doubleValue = parsedValue;
            } else {
                qWarning() << "Key" << key << "has a value that couldn't be parsed as double. Defaulting to 0.00.";
            }
        }

        // Format the value to 2 decimal places
        QString formattedValue = QString::asprintf("%.02f", doubleValue);

        // Use the standard block creation
        QWidget *block = createBasicBlock(key, formattedValue);
        mainLayout->addWidget(block);
    }

    for (const QString &key : variantMap.keys()) {
        const QVariant &value = variantMap[key];

        if (key == "_placeholder") {
            continue;
        }

        // If the key hasn't been processed in the desiredOrder loop
        if (!processedKeys.contains(key))
        {
            if (value.canConvert<double>()) {
                double doubleValue = value.toDouble();
                QString formattedValue = QString::asprintf("%.02f", doubleValue);

                // Use the new block creation for deletable items
                QWidget *block = createDeletableBlock(key, formattedValue); 
                mainLayout->addWidget(block);
            } else {
                qWarning() << "Key" << key << "has a non-numeric value or could not be converted, skipping.";
            }
        }
    }

    mainLayout->addStretch();
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(contentWidget);
}

// Creates visual blocks for aset bukan semasa
void BlockManager::createAbsAccountBlocks(const QVariantMap &variantMap, Ui::MainWindow *m_ui, QScrollArea *scrollArea, QWidget *contentWidget)
{
    if (!scrollArea) {
        qCritical() << "Error: QScrollArea not found in UI file.";
        return;
    }

    // Clear the list of input fields and their initial values before creating new ones
    m_AbsBlockInputs.clear(); 

    // Check if the content widget exists and has a layout. If not, create a new layout
    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout*>(contentWidget->layout());
    if (!mainLayout) {
        mainLayout = new QVBoxLayout(contentWidget);
        mainLayout->setSpacing(10);
        mainLayout->setAlignment(Qt::AlignTop);
    } else {
        // Clear existing widgets in the layout before adding new ones
        QLayoutItem *item;
        while ((item = mainLayout->takeAt(0)) != nullptr) {
            if (item->widget()) {
                item->widget()->deleteLater();
            }
            delete item;
        }
    }

    for (const QString &key : variantMap.keys()) {
        const QVariant &keyMap = variantMap[key];

        if (key == "_placeholder") {
            continue;
        }

        if (!keyMap.canConvert<QVariantMap>()) {
            qWarning() << "Key" << key << "is not in the correct format, skipping.";
            continue;
        }

        QVariantMap innerMap = keyMap.toMap();
        if (!innerMap.contains("value") || !innerMap.contains("deprecatedValue")) {
            qWarning() << "Key" << key << "is missing 'value' or 'deprecatedValue'.";
            continue;
        }

        const QVariant &value = innerMap.value("value");
        const QVariant &deprecatedValue = innerMap.value("deprecatedValue");

        // Check if both value can be converted to double
        if (!innerMap.contains("value") || !innerMap.contains("deprecatedValue")) {
            qWarning() << "Key" << key << "has a non-numeric value or could not be converted, skipping.";
            continue;
        }

        // Convert both value to 2 decimals place
        QString formattedValue = QString::asprintf("%.02f", value.toDouble());
        QString formattedDeprecatedValue = QString::asprintf("%.02f", deprecatedValue.toDouble());

        QWidget *block = createAbsBlock(key, formattedValue, formattedDeprecatedValue); 
        mainLayout->addWidget(block);
    }

    mainLayout->addStretch();
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(contentWidget);
}

// Create basic block
QWidget* BlockManager::createBasicBlock(const QString &key, QString value)
{
    // Create a container widget for the block
    QFrame *blockFrame = new QFrame;
    blockFrame->setFrameShape(QFrame::StyledPanel);
    blockFrame->setLineWidth(1);
    blockFrame->setMidLineWidth(0);
    blockFrame->setStyleSheet("QFrame {background-color: #262626; border: 1px solid #e6e6e6; border-radius: 3px;}");

    // Horizontal layout for the key and value
    QHBoxLayout *blockLayout = new QHBoxLayout(blockFrame);

    // Display account name on the left
    QLabel *keyLabel = new QLabel(key);
    keyLabel->setFont(QFont("Arial", 16, QFont::Bold));
    keyLabel->setStyleSheet("QLabel {background-color: #262626; color: #E2E8F0; border: none; padding-left: 10px;}");

    // Display account amount on the right in a QLineEdit
    QLineEdit *valueEdit = new QLineEdit;
    valueEdit->setObjectName(key);
    valueEdit->setText(value);
    valueEdit->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    // Check for 2 decimal places input
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(
        QRegularExpression("^\\d*(\\.\\d{0,2})?$"), valueEdit
    );
    valueEdit->setValidator(validator);

    valueEdit->setStyleSheet(
        "QLineEdit {background-color: #181818; color: #E2E8F0; border: none; padding: 5px;"
                    "min-width: 120px; border-radius: 2px; font-size: 16px;}"
    );

    // Reformat the text when the user is finished editing
    connect(valueEdit, &QLineEdit::editingFinished, this, &BlockManager::reformatValueOnFinish);

    // Store the initial value in the map
    m_accountValueInputs.insert(valueEdit, value);

    // Add widgets to the layout
    blockLayout->addWidget(keyLabel, 1);     // keyLabel takes a larger stretch factor
    blockLayout->addWidget(valueEdit, 0);    // valueEdit takes minimal space

    // Set an appropriate minimum height for the block
    blockFrame->setMinimumHeight(60);
    // Ensure the block takes up the full width
    blockFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    return blockFrame;
}

// Create block with a delete button
QWidget* BlockManager::createDeletableBlock(const QString &key, QString value)
{
    // Create a container widget for the block
    QFrame *blockFrame = new QFrame;
    blockFrame->setFrameShape(QFrame::StyledPanel);
    blockFrame->setLineWidth(1);
    blockFrame->setMidLineWidth(0);
    blockFrame->setStyleSheet("QFrame {background-color: #262626; border: 1px solid #e6e6e6; border-radius: 3px;}");

    // Horizontal layout for the key and value
    QHBoxLayout *blockLayout = new QHBoxLayout(blockFrame);

    // Display account name on the left
    QLineEdit *keyEdit = new QLineEdit;
    keyEdit->setText(key);
    keyEdit->setFont(QFont("Arial", 16, QFont::Bold));
    keyEdit->setStyleSheet(
        "QLineEdit {background-color: #181818; color: #E2E8F0; border: none; padding: 5px;"
                    "min-width: 120px; border-radius: 2px; font-size: 16px;}"
    );

    // Display account amount on the right in a QLineEdit
    QLineEdit *valueEdit = new QLineEdit;
    valueEdit->setObjectName(key);
    valueEdit->setText(value);
    valueEdit->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    
    // Check for 2 decimal places input
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(
        QRegularExpression("^\\d*(\\.\\d{0,2})?$"), valueEdit
    );
    valueEdit->setValidator(validator);

    valueEdit->setStyleSheet(
        "QLineEdit {background-color: #181818; color: #E2E8F0; border: none; padding: 5px;"
                    "min-width: 120px; border-radius: 2px; font-size: 16px;}"
    );

    // Reformat the text when the user is finished editing
    connect(valueEdit, &QLineEdit::editingFinished, this, &BlockManager::reformatValueOnFinish);

    // Check for duplicate keys
    connect(keyEdit, &QLineEdit::editingFinished, this, [this, keyEdit, valueEdit]() {
        QString oldKey = valueEdit->objectName();
        QString newKey = keyEdit->text();

        // Skip if key didn't change
        if (oldKey == newKey) {
            return;
        }

        // Check if the new key is a duplicate of another existing key
        if (m_activeKeys.contains(newKey)) {
            qWarning() << "Key " << newKey << " already exists";
            keyEdit->setText(oldKey);
        } 
        else {
            // Update the key in the tracking set
            m_activeKeys.remove(oldKey);
            m_activeKeys.insert(newKey);
            
            // Update m_accountValueInputs
            valueEdit->setObjectName(newKey);
        }
    });

    // Store the initial value in the map
    m_accountValueInputs.insert(valueEdit, value);

    // Delete button
    QPushButton *deleteButton = new QPushButton("X", blockFrame);
    deleteButton->setFixedSize(30, 30);
    deleteButton->setFont(QFont("Arial", 14, QFont::Bold));
    deleteButton->setStyleSheet("QPushButton {background-color: #550404; color: #e6e6e6; border: 1px solid #cccccc; border-radius: 5px;}"
                                "QPushButton:hover {background-color: #990505;}"
                                "QPushButton:pressed {background-color: #4c0808;}"
    );
    
    // Connect the button to a slot to delete the block
    connect(deleteButton, &QPushButton::clicked, this, [blockFrame, valueEdit, this]() {
        // Remove the QLineEdit from the map
        m_accountValueInputs.remove(valueEdit);
        
        // Delete the block widget
        blockFrame->deleteLater();

        qDebug() << "Removed block for key:" << valueEdit->objectName();;
    });

    // Add widgets to the layout
    blockLayout->addWidget(keyEdit, 1);
    blockLayout->addWidget(deleteButton, 0);
    blockLayout->addWidget(valueEdit, 0);  

    // Set an appropriate minimum height for the block
    blockFrame->setMinimumHeight(60);
    // Ensure the block takes up the full width
    blockFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    return blockFrame;
}

// Create block for aset bukan semasa
QWidget* BlockManager::createAbsBlock(const QString &key, QString value, QString deprecatedValue)
{
    // Create a container widget for the block
    QFrame *blockFrame = new QFrame;
    blockFrame->setFrameShape(QFrame::StyledPanel);
    blockFrame->setLineWidth(1);
    blockFrame->setMidLineWidth(0);
    blockFrame->setStyleSheet("QFrame { background-color: #262626; border: 1px solid #e6e6e6; border-radius: 3px; }");

    // Horizontal layout for all elements
    QHBoxLayout *blockLayout = new QHBoxLayout(blockFrame);

    // Display account name on the left
    QLineEdit *keyEdit = new QLineEdit;
    keyEdit->setText(key);
    keyEdit->setFont(QFont("Arial", 16, QFont::Bold));
    keyEdit->setStyleSheet(
        "QLineEdit { background-color: #181818; color: #E2E8F0; border: none; padding: 5px;"
                    "min-width: 120px; border-radius: 2px; font-size: 16px; }"
    );

    // Display amount input on the right
    QLineEdit *amountEdit = new QLineEdit;
    amountEdit->setObjectName(key); // Use objectName to track the key
    amountEdit->setText(value);
    amountEdit->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    // Display deprecated value input on the right
    QLineEdit *deprecatedCostEdit = new QLineEdit;
    deprecatedCostEdit->setText(deprecatedValue);
    deprecatedCostEdit->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    // Shared stylesheet and validator for value inputs
    QString valueStyleSheet = "QLineEdit { background-color: #181818; color: #E2E8F0; border: none; padding: 5px;"
                              "border-radius: 2px; font-size: 16px; }";
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(
        QRegularExpression("^\\d*(\\.\\d{0,2})?$"), this
    );

    amountEdit->setStyleSheet(valueStyleSheet);
    amountEdit->setObjectName(key);
    amountEdit->setValidator(validator);
    amountEdit->setFixedWidth(120);

    deprecatedCostEdit->setStyleSheet(valueStyleSheet);
    deprecatedCostEdit->setValidator(validator);
    deprecatedCostEdit->setFixedWidth(120);

    // Reformat the text when the user is finished editing
    connect(amountEdit, &QLineEdit::editingFinished, this, [amountEdit, deprecatedCostEdit, value]() {
        // Get values
        bool okCurrent, okDeprecated;
        double currentVal = amountEdit->text().toDouble(&okCurrent);
        double deprecatedVal = deprecatedCostEdit->text().toDouble(&okDeprecated);

        if (!okCurrent) currentVal = 0.0;
        if (!okDeprecated) deprecatedVal = 0.0;
        
        // Check if current value is less than deprecated value
        if (currentVal < deprecatedVal) {
            // Reset to the initial value
            bool okInitial;
            double initialVal = value.toDouble(&okInitial);
            if (!okInitial) initialVal = 0.0;
            
            // Reformat the current value
            amountEdit->setText(QString::number(initialVal, 'f', 2));
        } else {
            // Reformat the current value
            amountEdit->setText(QString::number(currentVal, 'f', 2));
        }
    });

    connect(deprecatedCostEdit, &QLineEdit::editingFinished, this, [amountEdit, deprecatedCostEdit, deprecatedValue]() {
        // Get values
        bool okCurrent, okDeprecated;
        double currentVal = amountEdit->text().toDouble(&okCurrent);
        double deprecatedVal = deprecatedCostEdit->text().toDouble(&okDeprecated);

        if (!okCurrent) currentVal = 0.0;
        if (!okDeprecated) deprecatedVal = 0.0;
        
        // Check if current value is less than deprecated value
        if (currentVal < deprecatedVal) {
            // Reset to the initial value
            bool okInitial;
            double initialDeprecatedVal = deprecatedValue.toDouble(&okInitial);
            if (!okInitial) initialDeprecatedVal = 0.0;
            
            // Reformat the current value
            deprecatedCostEdit->setText(QString::number(initialDeprecatedVal, 'f', 2));
        } else {
            // Reformat the current value
            deprecatedCostEdit->setText(QString::number(deprecatedVal, 'f', 2));
        }
    });

    // Check for duplicate keys
    connect(keyEdit, &QLineEdit::textChanged, this, [this, keyEdit, amountEdit]() {
        QString oldKey = amountEdit->objectName();
        QString newKey = keyEdit->text();

        // Skip if key didn't change
        if (oldKey == newKey) {
            return;
        }

        if (m_activeKeys.contains(newKey)) {
            qWarning() << "Key " << newKey << " already exists.";
            keyEdit->setText(oldKey); // Revert to the old key
        } else {
            // Update the key in the tracking set
            m_activeKeys.remove(oldKey);
            m_activeKeys.insert(newKey);
            
            // Update the object name used for tracking
            amountEdit->setObjectName(newKey);
            
            // Update the key in our main data map
            QPair<QLineEdit*, QLineEdit*> widgets = m_AbsBlockInputs.take(oldKey);
            m_AbsBlockInputs.insert(newKey, widgets);
        }
    });

    // Store the pair of QLineEdit pointers in the map
    m_AbsBlockInputs.insert(key, {amountEdit, deprecatedCostEdit});

    // Delete button
    QPushButton *deleteButton = new QPushButton("X", blockFrame);
    deleteButton->setFixedSize(30, 30);
    deleteButton->setFont(QFont("Arial", 14, QFont::Bold));
    deleteButton->setStyleSheet("QPushButton { background-color: #550404; color: #e6e6e6; border: 1px solid #cccccc; border-radius: 5px; }"
                                "QPushButton:hover { background-color: #990505; }"
                                "QPushButton:pressed { background-color: #4c0808; }");
    
    // Delete the block
    connect(deleteButton, &QPushButton::clicked, this, [this, blockFrame, amountEdit]() {
        QString keyToRemove = amountEdit->objectName();
        
        // Remove from the data map
        m_AbsBlockInputs.remove(keyToRemove);
        m_activeKeys.remove(keyToRemove);

        // Delete the entire block widget
        blockFrame->deleteLater();

        qDebug() << "Removed block for key:" << keyToRemove;
    });

    // Add widgets to the layout in the desired order
    blockLayout->addWidget(keyEdit, 1);             // Key (stretches)
    blockLayout->addWidget(deleteButton, 0);        // Delete button
    blockLayout->addWidget(amountEdit, 0);          // Amount input
    blockLayout->addWidget(deprecatedCostEdit, 0);  // Deprecated cost input

    blockFrame->setMinimumHeight(60);
    blockFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    return blockFrame;
}

// Returns a map of account and it's current value
QVariantMap BlockManager::getAllValueMap() const
{
    QVariantMap allValuesMap;

    for (const QLineEdit *lineEdit : m_accountValueInputs.keys())
    {
        // Ensure the QLineEdit has a unique objectName set
        QString keyName = lineEdit->objectName();
        if (keyName.isEmpty()) {
            qWarning() << "ERROR: Empty keyName found! Skipping entry.";
            continue; 
        }

        // Insert the current text of the QLineEdit into the result map.
        allValuesMap.insert(keyName, lineEdit->text());
    }

    return allValuesMap;
}

// Returns a map of account for aset bukan semasa
QVariantMap BlockManager::getAbsValueMap() const
{
    QVariantMap allValuesMap;

    for (const QString &keyName : m_AbsBlockInputs.keys())
    {
        // Retrieve the pair of QLineEdit widgets for the current asset
        const QPair<QLineEdit*, QLineEdit*> &widgetPair = m_AbsBlockInputs.value(keyName);
        const QLineEdit *valueEdit = widgetPair.first;
        const QLineEdit *deprecatedValueEdit = widgetPair.second;

        // Create a nested map to store the value and deprecated value
        QVariantMap valueMap;

        // Get the double values from the line edits
        double value = valueEdit->text().toDouble();
        double deprecatedValue = deprecatedValueEdit->text().toDouble();

        valueMap.insert("value", QString::number(value, 'f', 2));
        valueMap.insert("deprecatedValue", QString::number(deprecatedValue, 'f', 2));

        // Add the nested map to the main map using the asset name as the key
        allValuesMap.insert(keyName, valueMap);
    }

    return allValuesMap;
}

// Slot to reformat the QLineEdit value when editing is finished
void BlockManager::reformatValueOnFinish()
{
    QLineEdit *valueEdit = qobject_cast<QLineEdit*>(sender());
    if (!valueEdit)
        return;

    // Get the current text and attempt conversion
    QString currentText = valueEdit->text();
    bool ok;
    double value = QLocale().toDouble(currentText, &ok);
    
    // Check the initial stored value for the fallback
    QString initialValue = m_accountValueInputs.value(valueEdit);

    if (ok) {        
        // Format the double with 2 decimal places
        QString formattedValue = QString::asprintf("%.02f", value);

        // Set the formatted text back to the QLineEdit
        valueEdit->setText(formattedValue);
        
    } else {        
        // Reset the QLineEdit text to its last known good value
        if (!initialValue.isNull() && !initialValue.isEmpty()) {
            valueEdit->setText(initialValue);
        } else {
            valueEdit->setText("0.00");
        }
    }
}