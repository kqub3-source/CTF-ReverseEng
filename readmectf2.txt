### Challenge Overview: Privilege Escalation Attack Simulation

You have been assigned a forensic task to analyze network traffic captured during a potential **privilege escalation attack** on a Windows 10 server. The attacker may have exfiltrated sensitive information. You need to investigate the PCAP file to identify any signs of malicious activity and uncover the hidden flag encoded in one of the packets.

The flag is encoded and hidden within the malicious network traffic, but the attacker has cleverly obscured it within the noise of legitimate traffic and 1000 fake packets. This flag will help you understand what privileges the attacker was able to escalate to.

---

### **Story: Privilege Escalation Attack**

The **Windows 10 server** running a critical service was compromised after a suspected vulnerability in an open SSH port (`Port 22`). The attacker successfully established a connection and uploaded a malicious payload. During the attack, they attempted to escalate privileges to gain access to restricted resources, most likely a critical flag. This flag, however, was encoded and exfiltrated within network packets, hidden amongst legitimate traffic.

### **Objective:**

1. **Analyze the PCAP file** (`privilege_escalation_attack.pcap`).
2. **Identify the malicious packet** where the attacker exfiltrates the flag.
3. **Extract the hidden flag** encoded within one of the packets.

---

### **Hints for Investigation:**

#### 1. **Step 1: Analyze TCP Handshake**
   - Start by filtering for TCP traffic, especially focusing on **Port 22** (SSH traffic).
   - Look for a **TCP handshake**: the sequence of packets (`SYN`, `SYN-ACK`, `ACK`). The attacker likely established a connection via this protocol.

   **Hint:** The malicious packet is likely part of the conversation established through this handshake. This will be your entry point into the malicious activity.

   **Wireshark Filter Example:**
   ```plaintext
   tcp.port == 22
   ```

#### 2. **Step 2: Investigate Suspicious Payload**
   - After identifying the TCP session on port 22, focus on the **data packets** within this session.
   - One of the packets sent by the attacker contains a suspicious payload with **hexadecimal encoded data**. This packet is part of the privilege escalation exploit.

   **Hint:** The payload doesn't resemble regular traffic; it looks encoded. Look for something abnormal in the data layer of a packet.

   **Wireshark Filter Example:**
   ```plaintext
   tcp.port == 22 and tcp.flags.push == 1
   ```

#### 3. **Step 3: Decode the Flag**
   - Once you've identified the malicious packet, you'll notice that the payload contains hexadecimal data, which doesn't appear readable.
   - The payload is actually a **hexadecimal-encoded flag**. Convert the payload back to its **ASCII representation** to retrieve the flag.

   **Hint:** You may find something resembling this format in hexadecimal:
   ```plaintext
   4354467b63306e67724074735f40646d696e7d
   ```

   - **Convert the hexadecimal** back to its ASCII equivalent. It will reveal the flag in the format:
   ```plaintext
   CTF{c0ngr@ts_@dmin}
   ```

   **Wireshark Tip:** Right-click on the packet and view its details. Look for the "Follow TCP Stream" option to inspect the payload more easily.

---

### **Step-by-Step Approach to Finding the Flag:**

1. **Open the PCAP file** in a network analysis tool like **Wireshark**.
2. **Filter TCP traffic** to only show traffic on **Port 22** (SSH) where the attacker established the malicious connection.
3. **Locate the payload** by inspecting data packets exchanged after the handshake.
4. **Identify the encoded payload**. Look for hexadecimal data that stands out, hinting at encoded information.
5. **Decode the payload** from hexadecimal back to ASCII to reveal the hidden flag.

   Use a tool or script to decode the hexadecimal string. For example, using Python:
   ```python
   hex_data = "4354467b63306e67724074735f40646d696e7d"
   decoded_flag = bytes.fromhex(hex_data).decode('utf-8')
   print(decoded_flag)
   ```

   This will output:
   ```plaintext
   CTF{c0ngr@ts_@dmin}
   ```

---

### **Privilege Escalation Attack Storyline:**

1. **TCP Handshake**: The attacker initiated a connection over SSH, attempting to connect to a vulnerable service running on **Port 22**.
2. **Payload Injection**: After establishing the connection, the attacker escalated their privileges using a crafted payload. This payload contained an encoded flag, representing their newly gained administrative access.
3. **Exfiltration**: The attacker then sent a final packet, embedding the flag in its payload, which they encoded to avoid detection.
4. **Cleanup**: The attacker continued to send several packets mimicking normal traffic to obfuscate the attack. Over 1000 fake packets were injected to blend the attack into legitimate traffic.

By finding the encoded flag hidden within the traffic, you've successfully uncovered the extent of the attack and revealed the secret message: **CTF{c0ngr@ts_@dmin}**.
