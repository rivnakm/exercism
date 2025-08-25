module LogLevels
open System.Text.RegularExpressions

let logMessageRegex = new Regex "\[([A-Z]+)\]: (.*)"

let message (logLine: string): string =
    let reMatch = logMessageRegex.Match logLine
    reMatch.Groups[2].Value.Trim()

let logLevel(logLine: string): string =
    let reMatch = logMessageRegex.Match logLine
    reMatch.Groups[1].Value.ToLower()

let reformat(logLine: string): string =
    let level = logLevel logLine
    let msg = message logLine

    $"{msg} ({level})"
