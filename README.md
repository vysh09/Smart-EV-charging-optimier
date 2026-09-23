# Smart EV Charging Station Optimizer

> Dynamic multi-bay load balancing powered by ESP32, MQTT telemetry, and edge machine learning.

**Author:** Vaishnavi K Reddy  
**Institution:** GM University  davangere

---

## Overview

The **Smart EV Charging Station Optimizer** is an intelligent load balancing system designed for multi-bay electric vehicle (EV) charging hubs. Built using ESP32 edge controllers, standardized MQTT messaging, and ThingsBoard cloud dashboards, the system dynamically manages bay-level power draw to enforce peak shaving and grid reliability while sustaining autonomous operations during cloud disconnections.

---

## System Architecture

The solution operates on a real-time three-layer stack:

### Layer Details

* **Layer 01 — Edge Sensing (ESP32 Per-Bay Controller):**
  * Emulates and monitors per-bay voltage and current telemetry.
  * Autonomous offline relay control for load switching.
  * Local Edge AI inference for real-time demand classification (`ALLOW`, `THROTTLE`, `DEFER`).
  * Decentralized failover sustains bay-level load throttling even during cloud disconnection.

* **Layer 02 — Communication (MQTT Broker Transport):**
  * Secure, lightweight telemetry delivery over ports `1883` / `8883`.
  * Standardized JSON payloads for cross-bay data aggregation.
  * Sub-second remote procedure call (RPC) command flow.

* **Layer 03 — Cloud & Rules (ThingsBoard Platform):**
  * Fleet dashboard for multi-bay monitoring and telemetry visualization.
  * Configurable rule chains for grid limit violations and operator alarms.
  * Automated peak-shaving dispatch engine.

## Repository Structure

```text
├── BAY1/                     # Bay 1 ESP32 PlatformIO firmware & simulation configs
│   ├── include/              # Peripherals, telemetry, rpc, state, and edge_ai headers
│   ├── src/                  # Firmware implementation and inference engine
│   └── platformio.ini        # PlatformIO environment configuration
├── BAY2/                     # Bay 2 ESP32 PlatformIO firmware
├── BAY3/                     # Bay 3 ESP32 PlatformIO firmware
└── README.md

