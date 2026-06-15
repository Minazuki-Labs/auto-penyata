#ifndef PDFMGENERATOR_H
#define PDFMGENERATOR_H 

#include <memory>
#include <QObject>
#include <QPdfWriter>

class PdfGenerator : public QObject
{
    Q_OBJECT
    
public:
    static void createAllPDF(const QMap<QString, QVariantMap> &data);

private:
    // Data struct
    struct AbsEntry {
        QString key;
        double kos;
        double snt;
        double bukuNilai;
    };
    struct UntungKasarData{
        // Jualan
        double jualan;
        double pulanganJualan;
        double jualanBersih;

        // Kos Jualan
        double inventoriAwal;
        double belian;
        double pulanganBelian;
        double belianBersih;
        QList<QPair<QString, double>> kosBelianAccount;
        double kosBelian;
        double kosBarangUntukDijual;
        double inventoriAkhir;
        double kosJualan;

        // Untung kasar / rugi kasar
        double untungKasar;

        // Flags for drawing logic
        bool hasPulanganBelian;
        bool hasKosBelianItems;
    };
    struct UntungBersihData{
        // Hasil
        QList<QPair<QString, double>> hasilAccount;
        double totalHasil = 0.0;

        // Belanja
        QList<QPair<QString, double>> belanjaAccount;
        double totalBelanja = 0.0;

        // Untung bersih
        double tambahHasil;
        double untungBersih;

        // Flags for drawing logic
        bool hasHasil;
        bool hasBelanja;
    };
    struct DebitData{
        // Aset bukan semasa
        QList<AbsEntry> AbsEntries;
        double totalAbs = 0.0;

        // Aset semasa
        QList<QPair<QString, double>> AsAccount;
        double inventoriAkhir;
        double akaunBelumTerima;
        double PeruntukanHutangRagu = 0.0;
        double actualABT = 0.0;
        double totalAs = 0.0;

        // Liabiliti semasa
        QList<QPair<QString, double>> LsAccount;
        double totalLs = 0.0;

        // Modal kerja
        double modalKerja;
        double totalDebit;

        // Flags for drawing logic
        bool hasPeruntukanHutangRagu = false;
        bool hasAbs = false;
        bool hasAs = false;
        bool hasLs = false;
    };
    struct CreditData{
        // Ekuiti Pemilik
        double modalAwal;
        double untungBersih;
        double jumlahModal;
        double ambilan;
        double modalAkhir;

        // Liabiliti bukan semasa
        QList<QPair<QString, double>> lbsAccount;
        double totalLbs = 0.0;

        // Total credit
        double totalCredit;

        // Flags for drawing logic
        bool hasLbs = false;
    };

    // Generate pdf
    static double createApurPdf(const QMap<QString, QVariantMap> &data);
    static void createPkkPdf(const QMap<QString, QVariantMap> &data, const double untungBersih);

    // Setup Pdf
    static std::unique_ptr<QPdfWriter> setupPDF(const QString& fullFilePath);
    static QString generateFilePath(QString fileName, QString companyName, QDate date);

    // Draw title and report name
    static int drawTitle(QPainter& painter, int yPos, QString companyName, QString reportName, int pageWidth);

    // Draw apur
    static int drawUntungKasar(QPainter& painter, QPdfWriter* writer, int yPos, const UntungKasarData& apurData, bool containHasilBelanja);
    static int drawUntungBersih(QPainter& painter, QPdfWriter* writer, int yPos, const UntungBersihData& data);
    static int drawDebit(QPainter& painter, QPdfWriter* writer, int yPos, const DebitData& data);
    static int drawCredit(QPainter& painter, QPdfWriter* writer, int yPos, const CreditData& data);

    // Calculate value
    static UntungKasarData calculateUntungKasar(const QVariantMap& data);
    static UntungBersihData calculateUntungBersih(const QVariantMap& hasilData, const QVariantMap& belanjaData, const double untungKasar);
    static DebitData calculateDebit(const QMap<QString, QVariantMap> &data);
    static CreditData calculateCredit(const QMap<QString, QVariantMap> &data, const double untungBersih);

    // Create a QRect for the value columns
    static QRect createValueRect(int xLeft, int yBaseLine, const QFontMetrics& fm);

    // Create row of account
    static int generateRow(QPainter& painter, QPdfWriter* writer, const QString& accountName, const QVariant& accountValue, int xCol, int yPos, bool neg = false);    
    static int generateAbsRow(QPainter& painter, QPdfWriter* writer, const QString& accountName, const QVariant& kos, const QVariant& snt, const QVariant& nilaiBuku, int yPos);

    // Draw line
    static void drawLine(QPainter& painter, int xCol, int yPos);

    // Draw header
    static int drawHeader(QPainter& painter, QPdfWriter* writer, const QString& header, int yPos);

    // Draw column header
    static int drawColumnHeader(QPainter& painter, int yPos, bool type = true);

    // Setup new page
    static int checkYPos(QPainter& painter, QPdfWriter* writer, int yPos);

    // Font
    static QFont titleFont;
    static QFont headerFont;
    static QFont regularFont;
    static QFont underlineFont;

    // Margin
    static const int margin;
    static const int xStartLeft;

    // Height and width
    static const int rectHeight;
    static const int columnWidth;

    // Define the three value column positions
    static const int xCol1;
    static const int xCol2;
    static const int xCol3;
};
#endif // PDFMGENERATOR_H