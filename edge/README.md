# Milk-V Duo 256M 边缘节点

`risk_fusion.c` 是可在 RISC-V Linux 环境运行的多模态风险融合参考程序。它接收温度、烟雾原始值、功耗和视觉置信度，输出结构化 JSON 风险事件。

```bash
gcc -O2 risk_fusion.c -o risk_fusion
./risk_fusion 46.2 1920 18.5 0.81
```

实际部署时，可由 MQTT 订阅程序将 ESP32-C3 遥测值与视觉模型输出传给该程序；当 `localAlarm` 为 `true` 时，节点立即触发 GPIO 声光告警并将事件写入离线队列。

Milk-V 官方提供 Duo 系列 Buildroot SDK，可用于生成 RISC-V 固件镜像。模型部署阶段可将目标检测模型量化为 INT8，并通过官方 TPU 工具链转换后在 SG2002 上运行。
