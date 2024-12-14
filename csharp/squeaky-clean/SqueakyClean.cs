using System;
using System.Text;

public static class Identifier
{
    public static string Clean(string identifier)
    {
        if (identifier == string.Empty)
        {
            return identifier;
        }

        var builder = new StringBuilder();

        for (var i = 0; i < identifier.Length; i++)
        {
            if (identifier[i] == ' ')
            {
                builder.Append('_');
                continue;
            }

            if (identifier[i] >= 'α' && identifier[i] <= 'ω')
            {
                continue;
            }

            if (char.IsControl(identifier[i]))
            {
                builder.Append("CTRL");
            }

            // Replace kebab-case with camelCase
            if (identifier[i] == '-')
            {
                i++;
                builder.Append(char.ToUpper(identifier[i]));
                continue;
            }

            if (!char.IsLetter(identifier[i]))
            {
                continue;
            }

            builder.Append(identifier[i]);
        }
        return builder.ToString();
    }
}
