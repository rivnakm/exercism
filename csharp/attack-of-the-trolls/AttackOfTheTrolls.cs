enum AccountType
{
    Guest,
    User,
    Moderator
}

[Flags]
enum Permission
{
    None = 0b000,
    Read = 0b001,
    Write = 0b010,
    Delete = 0b100,
    All = 0b111
}

static class Permissions
{
    public static Permission Default(AccountType accountType)
    {
        return accountType switch {
            AccountType.Guest => Permission.Read,
            AccountType.User => Permission.Read | Permission.Write,
            AccountType.Moderator => Permission.Read | Permission.Write | Permission.Delete,
            _ => Permission.None
        };
    }

    public static Permission Grant(Permission current, Permission grant)
    {
        return current | grant;
    }

    public static Permission Revoke(Permission current, Permission revoke)
    {
        return current & (~revoke);
    }

    public static bool Check(Permission current, Permission check)
    {
        return (current & check) == check;
    }
}
