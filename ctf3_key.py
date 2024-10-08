import binascii

SECRET_KEY = "super_secret_key"

def obfuscate(username):
    key_bytes = SECRET_KEY.encode()
    user_bytes = username.encode()

    # XOR each byte of the username with the secret key
    obfuscated = bytearray()
    for i in range(len(user_bytes)):
        obfuscated.append(user_bytes[i] ^ key_bytes[i % len(key_bytes)])

    # Return hex string representation of the obfuscated value
    return binascii.hexlify(obfuscated).decode()

username = "ctfplayer"
token = obfuscate(username)
print(f"Generated token for {username}: {token}")
