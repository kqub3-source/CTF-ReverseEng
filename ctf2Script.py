from scapy.all import *

# Base64 encode the flag
flag = "CTF{c0ngr@ts_@dmin}"
encoded_flag = flag.encode('utf-8').hex()

# Create a list of packets simulating network traffic (TCP)
packets = []

# Simulate TCP handshake (SYN, SYN-ACK, ACK)
tcp_syn = IP(dst="192.168.1.10")/TCP(dport=22, flags="S", seq=100)
tcp_synack = IP(dst="192.168.1.11")/TCP(dport=22, flags="SA", seq=101, ack=tcp_syn.seq + 1)
tcp_ack = IP(dst="192.168.1.10")/TCP(dport=22, flags="A", seq=tcp_synack.ack, ack=tcp_synack.seq + 1)

# Add handshake packets to the list
packets.append(tcp_syn)
packets.append(tcp_synack)
packets.append(tcp_ack)

# Create a malicious packet simulating an attack with the encoded flag in the payload
malicious_packet = IP(dst="192.168.1.10")/TCP(dport=22, flags="PA")/Raw(load=encoded_flag)
packets.append(malicious_packet)

# Simulate normal TCP traffic
normal_packet = IP(dst="192.168.1.10")/TCP(dport=445, flags="PA")/Raw(load="Normal SMB Traffic")
packets.append(normal_packet)

# Send some more random traffic
for i in range(5):
    random_packet = IP(dst="192.168.1.10")/TCP(dport=80, flags="PA")/Raw(load="GET /index.html")
    packets.append(random_packet)

# Save to a pcap file
wrpcap("privilege_escalation_attack.pcap", packets)

print("PCAP file 'privilege_escalation_attack.pcap' created successfully.")
