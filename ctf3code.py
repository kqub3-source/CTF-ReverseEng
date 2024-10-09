from flask import Flask, request, jsonify
import hashlib
import binascii

app = Flask(__name__)

# Server-side secret key, which participants must not know but reverse-engineer
SECRET_KEY = "super_secret_key"

# Flag to retrieve
FLAG = "CTF{R3v3rs3_Engin33ring_Fun}"

def obfuscate(username):
    """
    This function takes the username, combines it with the secret key, 
    and applies a transformation to generate the token.
    """
    key_bytes = SECRET_KEY.encode()
    user_bytes = username.encode()

    # XOR each byte of the username with the secret key
    obfuscated = bytearray()
    for i in range(len(user_bytes)):
        obfuscated.append(user_bytes[i] ^ key_bytes[i % len(key_bytes)])

    # Return hex string representation of the obfuscated value
    return binascii.hexlify(obfuscated).decode()

@app.route('/login', methods=['POST'])
def login():
    data = request.json

    if not data or 'username' not in data or 'token' not in data:
        return jsonify({"message": "Invalid request, username and token are required"}), 400

    username = data['username']
    token = data['token']

    # Generate the correct token based on the server-side algorithm
    correct_token = obfuscate(username)

    if token == correct_token:
        return jsonify({
            "message": "Login successful!",
            "flag": FLAG
        }), 200
    else:
        return jsonify({"message": "Invalid token"}), 403

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
