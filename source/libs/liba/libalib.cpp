#include "libalib.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QDebug>

LibALib::LibALib()
{
}

QStringList LibALib::parseFileName(const QString &p_file_name)
{
    QStringList output;
    QRegularExpression re("^(.+)-(.+)-(.+)-(.+)-(.+)-(\\d+).log$");
    QRegularExpressionMatch match = re.match(p_file_name);
    if (!match.hasMatch())
    {
        qDebug() << "parseFileName error " << p_file_name << Qt::endl;
        return output;
    }
    const QString category = match.captured(1);
    const QString type = match.captured(2);
    const QString domain = match.captured(3);
    const QString id = match.captured(4);
    const QString servername = match.captured(5);
    const QString date = match.captured(6);

    output << category << type << domain << id << servername << date;

    return output;
}

QStringList LibALib::parseForScriptError(const QString &p_content_part)
{
    QStringList results;
    QRegularExpression re("\\[(\\d{4}-.+)\\] .+ Error while executing script \\'(.+)\\': (.+): (.+)\\n((.+\\n)+\\n)");
    QRegularExpressionMatch match = re.match(p_content_part);
    if (!match.hasMatch())
    {
        return results;
    }

    const QString date = match.captured(1);
    const QString file_name = match.captured(2);
    const QString error_type = match.captured(3);
    const QString error_message = match.captured(4);
    const QString call_stack = match.captured(5);

    results << date << file_name << error_type << error_message << call_stack;

    return results;
}

QStringList LibALib::parseForScriptErrorParts(const QString &p_full_content)
{

    QStringList output;
    QRegularExpression re("\\[.+\\] .+ Error while executing script(?:.+\\n)+\\n");
    QRegularExpressionMatchIterator match = re.globalMatch(p_full_content);

    while (match.hasNext())
    {
        QRegularExpressionMatch part = match.next();

        output << part.captured(0);
    }

    return output;
}
