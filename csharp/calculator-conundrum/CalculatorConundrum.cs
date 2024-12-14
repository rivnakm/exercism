using System;

public static class SimpleCalculator
{
    public static string Calculate(int operand1, int operand2, string operation)
    {
        ArgumentNullException.ThrowIfNull(operation);
        if (string.IsNullOrEmpty(operation))
        {
            throw new ArgumentException();
        }

        if (operation == "/" && operand2 == 0)
        {
            return "Division by zero is not allowed.";
        }

        var result = operation switch
        {
            "+" => operand1 + operand2,
            "*" => operand1 * operand2,
            "/" => operand1 / operand2,
            _ => throw new ArgumentOutOfRangeException()
        };


        return $"{operand1} {operation} {operand2} = {result}";
    }
}
