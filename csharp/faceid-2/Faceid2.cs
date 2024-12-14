using System;
using System.Collections.Generic;

public class FacialFeatures
{
    public string EyeColor { get; }
    public decimal PhiltrumWidth { get; }

    public FacialFeatures(string eyeColor, decimal philtrumWidth)
    {
        EyeColor = eyeColor;
        PhiltrumWidth = philtrumWidth;
    }

    public bool Equals(FacialFeatures other)
    {
        return this.EyeColor == other.EyeColor && this.PhiltrumWidth == other.PhiltrumWidth;
    }

    public override bool Equals(object other)
    {
        if (other == null)
        {
            return false;
        }

        FacialFeatures ff = other as FacialFeatures;
        if (ff == null)
        {
            return false;
        }
        else
        {
            return this.Equals(ff);
        }
    }

    public override int GetHashCode()
    {
        return HashCode.Combine(this.EyeColor.GetHashCode(), this.PhiltrumWidth.GetHashCode());
    }
}

public class Identity
{
    public string Email { get; }
    public FacialFeatures FacialFeatures { get; }

    public Identity(string email, FacialFeatures facialFeatures)
    {
        Email = email;
        FacialFeatures = facialFeatures;
    }

    public bool Equals(Identity other)
    {

        return this.Email == other.Email && this.FacialFeatures.Equals(other.FacialFeatures);
    }
    public override bool Equals(object other)
    {
        if (other == null)
        {
            return false;
        }

        Identity ident = other as Identity;
        if (ident == null)
        {
            return false;
        }
        else
        {
            return this.Equals(ident);
        }
    }

    public override int GetHashCode()
    {
        return HashCode.Combine(this.Email.GetHashCode(), this.FacialFeatures.GetHashCode());
    }
}

public class Authenticator
{
    private HashSet<Identity> _registeredIdentities = new HashSet<Identity>();

    public static bool AreSameFace(FacialFeatures faceA, FacialFeatures faceB)
    {
        return faceA.Equals(faceB);
    }

    public bool IsAdmin(Identity identity)
    {
        return identity.Email == "admin@exerc.ism" && identity.FacialFeatures.PhiltrumWidth == 0.9m && identity.FacialFeatures.EyeColor == "green";
    }

    public bool Register(Identity identity)
    {
        if (this._registeredIdentities.Contains(identity))
        {
            return false;
        }
        else
        {
            this._registeredIdentities.Add(identity);
            return true;
        }
    }

    public bool IsRegistered(Identity identity)
    {
        return this._registeredIdentities.Contains(identity);
    }

    public static bool AreSameObject(Identity identityA, Identity identityB)
    {
        return object.ReferenceEquals(identityA, identityB);
    }
}
