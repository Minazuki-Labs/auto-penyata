#include "header/jsonmanager.h"

#include <QDir>
#include <QStandardPaths>
#include <QJsonDocument>
#include <QJsonObject>

JsonManager::JsonManager(QObject *parent)
    : QObject(parent)
{
    // Ensure the Application Support directory exists on startup
    QDir dir(getAppFilePath(""));
    dir.mkpath(dir.path());
}

/**
 * @brief Constructs platform-specific path to the JSON
 *
 * @param fileName The name of the file [Ex. data.json]
 * @return Full path to the specific JSON
 */
QString JsonManager::getAppFilePath(const QString& fileName)
{
    // Get the standard location for application data
    QString configDir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);

    // Construct the full path by appending the specific file name
    QDir dir(configDir);

    return dir.filePath(fileName);
}

/**
 * @brief Reads data from JSON file
 *
 * @param fileName The name of the JSON file to read
 * @return A QVariantMap containing the settings, or an empty map on failure
 */
QVariantMap JsonManager::readJson(const QString& fileName)
{
    QString filePath = getAppFilePath(fileName);
    QFile file(filePath);
    
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open config file for reading:" << filePath;
        return QVariantMap(); // Return an empty map, representing no JSON found
    }
    
    QByteArray data = file.readAll();
    file.close();
    
    QJsonDocument doc = QJsonDocument::fromJson(data);

    if (doc.isNull() || !doc.isObject()) {
        qWarning() << "Failed to parse valid JSON object from:" << filePath;
        return QVariantMap();
    }

    if (doc.isEmpty()) {
        qWarning() << filePath << "is empty. Cannot load value";
        return QVariantMap();
    }

    // Convert the root QJsonObject to a QVariantMap
    return doc.object().toVariantMap();
}

/**
 * @brief Reads data from all JSON files
 * @return A QMap where the key is the file name and the value is the QVariantMap
 * of the JSON data. Files that fail to load will have an empty QVariantMap
 * as their value.
 */
QMap<QString, QVariantMap> JsonManager::readAllJson()
{
    QMap<QString, QVariantMap> allData;
    QStringList fileNames = {"apur.json", "aset_bukan_semasa.json", "aset_semasa.json", "belanja.json", "ekuiti_pemilik.json",
                             "hasil.json", "liabiliti_bukan_semasa.json", "liabiliti_semasa.json", "setting.json"};

    for (const QString& fileName : fileNames) {
        // Get the data from Json
        QVariantMap fileData = readJson(fileName);
        allData.insert(fileName, fileData);

        // Check if read is successful
        if (!fileData.isEmpty()) {
            qDebug() << "Successfully loaded JSON data from:" << fileName;
        } else {
            qWarning() << "Returned empty data for file:" << fileName << "(see previous warning for details)";
        }
    }

    return allData;
}

/**
 * @brief Writes the data in QVariantMap to a JSON file
 *
 * @param fileName The name of the JSON file to write
 * @param datas The map of datas to save
 * @return true if the write was successful, false otherwise
 */
bool JsonManager::writeJson(const QString& fileName, const QVariantMap& datas)
{
    QString filePath = getAppFilePath(fileName);

    // Ensure directory path exists
    QDir dir = QFileInfo(filePath).dir();
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            qCritical() << "Failed to create configuration directory:" << dir.path();
            return false;
        }
    }

    // Convert and write the data from a QVariantMap to a QJsonDocument
    QJsonObject rootObject = QJsonObject::fromVariantMap(datas);
    QJsonDocument doc(rootObject);
    
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qCritical() << "Could not open config file for writing:" << filePath;
        return false;
    }
    
    // Write the JSON data with a human-readable indentation format
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
    
    qDebug() << "Successfully saved data to:" << filePath;
    return true;
}

// Setup initial JSON
void JsonManager::initialJsonSetup()
{
    // Initial data for setup
    QString todayDate = QDate::currentDate().toString("yyyy/MM/dd");
    static const std::vector<JsonSetupItem> ALL_JSON_FILES = {
        {"apur.json", {
            {"Jualan", 0.0},
            {"Belian", 0.0},
            {"Pulangan Jualan", 0.0},
            {"Pulangan Belian", 0.0},
            {"Inventori Awal", 0.0},
            {"Inventori Akhir", 0.0},
            {"Angkutan Masuk", 0.0},
            {"Upah Atas Belian", 0.0},
            {"Duti Import", 0.0},
            {"Insurans Atas Belian", 0.0},
            {"_placeholder", true}
        }},

        {"belanja.json", {
            {"_placeholder", true}
        }},

        {"hasil.json", {
            {"_placeholder", true}
        }},

        {"aset_bukan_semasa.json", {
            {"_placeholder", true}
        }},

        {"aset_semasa.json", {
            {"Tunai", 0.0},
            {"Bank", 0.0},
            {"Akaun Belum Terima", 0.0},
            {"Peruntukan Hutang Ragu", 0.0},
            {"_placeholder", true}
        }},

        {"liabiliti_bukan_semasa.json", {
            {"_placeholder", true}
        }},

        {"liabiliti_semasa.json", {
            {"Akaun Belum Bayar", 0.0},
            {"_placeholder", true}
        }},

        {"ekuiti_pemilik.json", {
            {"Modal Awal", 0.0},
            {"Ambilan", 0.0},
            {"_placeholder", true}
        }},

        {"setting.json", {
            {"CompanyName", "YourCompanyName"},
            {"Date", todayDate},
        }},
    };

    // The loop iterates over all files and creates them if necessary 
    for (const auto& item : ALL_JSON_FILES)
    {
        // Read the existing file
        QVariantMap datas = readJson(item.fileName);
        bool writeRequired = false;

        // File is missing or empty, write initial data
        if (datas.isEmpty())
        {
            qInfo() << "Initializing" << item.fileName << "with initial data.";
            datas = item.defaultData;
            writeRequired = true;
        }
        // File exists, check for missing keys
        else
        {
            for (auto it = item.defaultData.constBegin(); it != item.defaultData.constEnd(); ++it)
            {
                const QString& key = it.key();

                if (!datas.contains(key))
                {
                    datas.insert(key, it.value());
                    qWarning() << "Missing key found and added in" << item.fileName << ":" << key;
                    writeRequired = true;
                }
            }
        }

        // Write to JSON
        if (writeRequired)
        {
            writeJson(item.fileName, datas);
        }
    }
}

// Reset JSON
bool JsonManager::resetJSON()
{
    bool allFilesRemoved = true;
    QStringList json_to_reset = {
        "apur.json",
        "belanja.json",
        "hasil.json",
        "aset_bukan_semasa.json",
        "aset_semasa.json",
        "liabiliti_bukan_semasa.json",
        "liabiliti_semasa.json",
        "ekuiti_pemilik.json",
        "setting.json",
    };

    for (const auto& filename : json_to_reset) {
        QString filePath = getAppFilePath(filename);

        // Check if the file exist
        if (!QFile::exists(filePath)) {
            qWarning() << "File not found, skipping:" << filePath;
            continue;
        }

        // Attempt to remove the file
        if (QFile::remove(filePath)) {
            qDebug() << "Successfully removed file:" << filename;
        } else {
            qWarning() << "ERROR: Failed to remove file:" << filename;
            allFilesRemoved = false;
        }
    }

    initialJsonSetup();
    return allFilesRemoved;
}