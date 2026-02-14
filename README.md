# DNS Lookup Utility

This project is a low-level C application designed to resolve hostnames into IP addresses using the POSIX sockets. It demonstrates the transition from human-readable domain names to network-routable addresses.

---

## Project Purpose and Learning Outcomes

Deeper understanding of the **TCP/IP stack** and the **Linux Networking API**. Key takeaways:

* **Memory Management:** Handling dynamic memory allocation and pointer arithmetic in C, specifically when iterating through linked lists returned by system calls.
* **System Programming:** Implementing `getaddrinfo()` to perform protocol-independent name resolution.
* **Data Structures:** Interfacing with complex network structures like `addrinfo`, `sockaddr_in` (IPv4), and `sockaddr_in6` (IPv6).
* **Bitwise Operations and Type Casting:** Managing type conversions between generic `sockaddr` structures and specific address formats.

---

## How it Works:

The program functions by interacting directly with the operating system's resolver library. Below is the technical breakdown of the process:

### 1. The Resolver Configuration (`struct addrinfo`)

The application initializes a `hints` structure to define the criteria for the lookup. By setting `ai_family = AF_UNSPEC`, the program remains protocol-agnostic, allowing it to retrieve both IPv4 and IPv6 results simultaneously.

### 2. DNS Resolution via `getaddrinfo`

The core of the program is the `getaddrinfo()` system call. Unlike `gethostbyname()`, this function is thread-safe and supports the IPv6 standard. It queries the local DNS cache or reaches out to configured DNS servers to populate a linked list of `addrinfo` structures.

### 3. Binary to String Conversion

IP addresses are stored in the kernel as binary data. To make this human-readable, the program utilizes **`inet_ntop`:** A "Network to Presentation" function that converts binary IP addresses into ASCII strings.

### 4. Protocol Mapping

The program inspects the `ai_protocol` field within the socket structures to identify specific transport layers like **TCP (6)**, **UDP (17)**, or **ICMP (1)**.

---

## Project Structure

```text
.
├── bin/
│   └── run            # The compiled executable
├── src/
│   └── dns-lookup.c   # Source code
├── LICENSE            # Project license
└── README.md          # Documentation

```

---

## Usage

### Compilation

To compile the source code, use `gcc` or any standard C compiler:

```bash
gcc src/dns-lookup.c -o bin/run

```

### Execution

Run the binary followed by the hostname you wish to resolve:

```bash
./bin/run google.com

```

### Sample Output

```text
Starting DNS Lookup for google.com...
0
DNS LOOKUP for google.com
IPv4
    Address: 142.250.190.46
    Service: IP
IPv6
    Address: 2607:f8b0:4009:803::200e
    Service: IP

```
## Acknowledgments

This tool was developed following the technical principles and low-level networking concepts found in the man pages and **Beej's Guide to Network Programming**. I am grateful for the clarity and depth provided by this resource, which was instrumental in understanding how to bridge the gap between application-layer hostnames and transport-layer sockets.

You can find the reference material here: [Beej's Guide to Network Programming (PDF)](https://beej.us/guide/bgnet/pdf/bgnet_a4_c_1.pdf)
