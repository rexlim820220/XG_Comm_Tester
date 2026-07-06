# XG_Comm_Tester

A lightweight C++ utility for establishing TCP/IP communication with **Keyence XG-X Series** vision controllers. This tool allows users to send custom commands (CC commands) and receive real-time alignment data or status responses from the controller.

### Features

- **TCP/IP Socket Communication**: Implemented using Winsock2 for low-latency interaction.
- **Static Polymorphism**: Supports both parameterized and non-parameterized commands via function overloading.
- **Protocol Compliance**: Automatically formats parameters to meet XG-X requirements (Sign + 7-digit integer + 3-digit decimal).
- **Real-time Feedback**: Captures and displays both the Acknowledgement (Ack) and the Data response from the controller.

### Technical Specifications

- **Language**: C++
- **IDE**: Microsoft Visual Studio (MSVS)
- **Library**: `ws2_32.lib` (Winsock2)
- **Default Port**: 8500
- **Termination Character**: `CR` (`\r`)

### Communication Protocol

The tool follows the XG-X custom command format:
- **Request**: `CC, [CommandID], [Param1], [Param2], [Param3]\r`
- **Response 1 (Ack)**: `CC\r` or `ER, [ErrorCode]\r`
- **Response 2 (Data)**: `[Value1], [Value2], [Value3], [Value4]\r`

### Setup & Installation

1. **Clone the repository**:
   `git clone https://github.com/your-username/XG_Comm_Tester.git`

- Open in Visual Studio:
  - Open XG_Comm_Tester.sln.
  - Ensure the build configuration is set to x64 or x86.
- Network Configuration:
  - Set your PC's IP address to the same subnet as the XG-X controller (e.g., 192.168.0.100).
  - Ensure the controller's IP is correctly set in the XG_IP constant within the code.
- Build and Run:
  - Press F5 to compile and execute.

### Usage Example

```
// Example 1: Send a command without parameters (e.g., Reset)
sendXGCommand(4); 

// Example 2: Send a command with parameters (e.g., Calibration/Alignment)
sendXGCommand(117, 100.5, 200.1, 0.0);
```

### Troubleshooting
- Connection Failed: Check if the physical Ethernet cable is connected and the IP addresses are in the same subnet.
- ER Response: Ensure the CommandID is correctly mapped to a Pipeline/Trigger in the VisionEditor.
- Timeout: Verify that the controller's TCP/IP Server is enabled and the port (8500) is open.
- Developed for industrial vision system integration.