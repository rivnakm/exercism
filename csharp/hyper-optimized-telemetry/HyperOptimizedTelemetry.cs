public static class TelemetryBuffer
{
    private static class Prefix
    {
        public const byte USHORT = sizeof(ushort);
        public const byte SHORT = 256 - sizeof(short);
        public const byte UINT = sizeof(uint);
        public const byte INT = 256 - sizeof(int);
        public const byte LONG = 256 - sizeof(long);
    }

    public static byte[] ToBuffer(long reading)
    {
        var buffer = new byte[9];
        if (reading < int.MinValue) {
            buffer[0] = Prefix.LONG;
            BitConverter.GetBytes(reading).CopyTo(buffer, 1);
        } else if (reading < short.MinValue) {
            buffer[0] = Prefix.INT;
            BitConverter.GetBytes((int)reading).CopyTo(buffer, 1);
        } else if (reading < 0) {
            buffer[0] = Prefix.SHORT;
            BitConverter.GetBytes((short)reading).CopyTo(buffer, 1);
        } else if (reading <= ushort.MaxValue) {
            buffer[0] = Prefix.USHORT;
            BitConverter.GetBytes((ushort)reading).CopyTo(buffer, 1);
        } else if (reading <= int.MaxValue) {
            buffer[0] = Prefix.INT;
            BitConverter.GetBytes((int)reading).CopyTo(buffer, 1);
        } else if (reading <= uint.MaxValue) {
            buffer[0] = Prefix.UINT;
            BitConverter.GetBytes((uint)reading).CopyTo(buffer, 1);
        } else {
            buffer[0] = Prefix.LONG;
            BitConverter.GetBytes(reading).CopyTo(buffer, 1);
        }
        return buffer;
    }

    public static long FromBuffer(byte[] buffer)
    {
        var prefix = buffer[0];
        return prefix switch
        {
            Prefix.USHORT => BitConverter.ToUInt16(buffer, 1),
            Prefix.SHORT => BitConverter.ToInt16(buffer, 1),
            Prefix.UINT => BitConverter.ToUInt32(buffer, 1),
            Prefix.INT => BitConverter.ToInt32(buffer, 1),
            Prefix.LONG => BitConverter.ToInt64(buffer, 1),
            _ => 0L
        };
    }
}
