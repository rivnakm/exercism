abstract class Character(string characterType)
{
    public abstract int DamagePoints(Character target);

    public virtual bool Vulnerable() => false;

    public override string ToString()
    {
        return $"Character is a {characterType}";
    }
}

class Warrior : Character
{
    public Warrior() : base(nameof(Warrior))
    {
    }

    public override int DamagePoints(Character target)
    {
        return target.Vulnerable() ? 10 : 6;
    }
}

class Wizard : Character
{
    private bool _spellPrepared = false;
    public Wizard() : base(nameof(Wizard))
    {
    }

    public override int DamagePoints(Character target)
    {
        return this._spellPrepared ? 12 : 3;
    }

    public void PrepareSpell()
    {
        this._spellPrepared = true;
    }

    public override bool Vulnerable()
    {
        return !this._spellPrepared;
    }
}
