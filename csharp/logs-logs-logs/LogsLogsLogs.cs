using System;
using System.Text.RegularExpressions;

enum LogLevel
{
    Unknown = 0,
    Trace = 1,
    Debug = 2,
    Info = 4,
    Warning = 5,
    Error = 6,
    Fatal = 42,
}

static class LogLine
{
    public static LogLevel ParseLogLevel(string logLine)
    {
        var re = new Regex(@"\[(TRC|DBG|INF|WRN|ERR|FTL)\]:");
        var match = re.Match(logLine);

        if (match.Success)
        {
            return match.Groups[1].Value switch
            {
                "TRC" => LogLevel.Trace,
                "DBG" => LogLevel.Debug,
                "INF" => LogLevel.Info,
                "WRN" => LogLevel.Warning,
                "ERR" => LogLevel.Error,
                "FTL" => LogLevel.Fatal,
                _ => throw new ArgumentOutOfRangeException()
            };
        }
        else
        {
            return LogLevel.Unknown;
        }
    }

    public static string OutputForShortLog(LogLevel logLevel, string message)
    {
        return $"{(int)logLevel}:{message}";
    }
}
