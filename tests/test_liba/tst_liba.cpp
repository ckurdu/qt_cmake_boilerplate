#include <QtTest>
#include <QCoreApplication>
#include <QDebug>
#include "libalib.h"

// add necessary includes here

class logparser : public QObject
{
    Q_OBJECT

public:
    logparser();
    ~logparser();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1_data();
    void test_case2_data();
    void test_case3_data();
    void test_case4_data();
    void test_case1();
    void test_case2();
    void test_case3();
    void test_case4();

private:
    LibALib *m_log_parser = nullptr;
    QStringList m_parts;
    QString m_log_content;
    void loadFileContent();
};

logparser::logparser()
{
    m_log_parser = new LibALib();
}

logparser::~logparser()
{
}

void logparser::loadFileContent()
{

    const QString error_script_file_name = ":/test_data/error_script.log";
    QFile log_file(error_script_file_name);
    QString data;
    if (log_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        m_log_content = log_file.readAll();
    }
    else
    {
        QFAIL("Error : Log file couldn't open");
        return;
    }
    log_file.close();
}

void logparser::initTestCase()
{
    loadFileContent();
}

void logparser::cleanupTestCase()
{
}

void logparser::test_case1_data()
{
    qInfo() << "test_case1_data";
    QTest::addColumn<QString>("filename");
    QTest::addColumn<QStringList>("expectedresult");
    QStringList data_filenames;

    QTest::newRow("api-blade9") << "api-blade9-7.mon.demandware.net-0-appserver-20220522.log"
                                << QStringList({"api", "blade9", "7.mon.demandware.net", "0", "appserver", "20220522"});
    QTest::newRow("jobs-blade9") << "jobs-blade9-7.mon.demandware.net-0-appserver-20220525.log"
                                 << QStringList({"jobs", "blade9", "7.mon.demandware.net", "0", "appserver", "20220525"});
}

void logparser::test_case2_data()
{

    qInfo() << "test_case2_data";

    QTest::addColumn<QString>("content");
    QTest::addColumn<QStringList>("expectedresult");

    QTest::newRow("find script error") << m_log_content
                                       << QStringList(
                                              {"int_google_tag_manager/cartridge/controllers/Account.js",
                                               "Error: Route with this name does not exist (modules/server/server.js#195)",
                                               "at modules/server/server.js:195 (append)",
                                               "at int_reference_arch/cartridge/controllers/Account.js:638",
                                               "at int_cordial_sfra/cartridge/controllers/Account.js:3",
                                               "at int_google_tag_manager/cartridge/controllers/Account.js:5"});
}

void logparser::test_case3_data()
{

    const QString error_script_file_name = ":/test_data/error_script.log";
    QFile log_file(error_script_file_name);
    QString data;
    if (log_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        data = log_file.readAll();
    }
    else
    {
        return;
    }
    log_file.close();

    QTest::addColumn<QString>("content");
    QTest::addColumn<int>("expectedresult");

    QTest::newRow("find script error") << data << 14;
}

void logparser::test_case4_data()
{

    QStringList parts = m_log_parser->parseForScriptErrorParts(m_log_content);
    qInfo() << "Part 1" << parts.at(1);
    QTest::addColumn<QString>("content");
    QTest::addColumn<QStringList>("expectedresult");
    QTest::newRow("find script error") << parts.at(0)
                                       << QStringList{"2022-05-23 15:48:51.360 GMT",
                                                      "int_google_tag_manager/cartridge/controllers/Account.js",
                                                      "Error",
                                                      "Route with this name does not exist (modules/server/server.js#195)",
                                                      "	at modules/server/server.js:195 (append)"
                                                      "	at int_reference_arch/cartridge/controllers/Account.js:638"
                                                      "	at int_cordial_sfra/cartridge/controllers/Account.js:3"
                                                      "	at int_google_tag_manager/cartridge/controllers/Account.js:5"};
}
void logparser::test_case1()
{
    QFETCH(QString, filename);
    QFETCH(QStringList, expectedresult);

    QStringList actualresult;

    QBENCHMARK
    {
        actualresult = m_log_parser->parseFileName(filename);
    }

    QCOMPARE(actualresult, expectedresult);
}

void logparser::test_case2()
{
    QFETCH(QString, content);
    QFETCH(QStringList, expectedresult);
}

void logparser::test_case3()
{
    QFETCH(QString, content);
    QFETCH(int, expectedresult);

    QStringList parts = m_log_parser->parseForScriptErrorParts(content);
    m_parts = parts;

    QCOMPARE(parts.count(), expectedresult);
}

void logparser::test_case4()
{
    QFETCH(QString, content);
    QFETCH(QStringList, expectedresult);
    QStringList actual_result = m_log_parser->parseForScriptError(content);
    QCOMPARE(actual_result, expectedresult);
}

QTEST_MAIN(logparser)

#include "tst_liba.moc"
