# 智巡开源

基于边缘 AI 的多场景智能巡检与预警系统，面向校园实验室、机房和小型仓储场景。

## 在线体验

[打开 GitHub Pages 演示](https://han-2233.github.io/zhixun-edge-ai/)

页面为纯静态应用，无需 GPT、ChatGPT 或其他账号登录。数据默认保留在当前浏览器中，摄像头画面仅在本机处理。

## 参赛提交材料

- 代码仓库：[GitHub 开源仓库](https://github.com/Han-2233/zhixun-edge-ai)
- 作品介绍文档：[项目介绍 PDF](https://han-2233.github.io/zhixun-edge-ai/assets/zhixun-project-introduction.pdf)
- 作品演示视频：[核心功能演示](https://han-2233.github.io/zhixun-edge-ai/assets/zhixun-demo.webm)

## 项目亮点

- 边缘优先：检测和规则判断在本地完成，低延迟、断网可用。
- 多模态融合：视觉、温湿度、烟雾与功耗数据共同判断风险。
- 隐私保护：默认不上传原始视频，只同步结构化事件。
- RISC-V 开源硬件：ESP32-C3 感知节点与 Milk-V Duo 256M 边缘 AI 节点协同运行。
- 告警闭环：异常发现、告警、人工确认与处置记录全流程可追溯。

## 快速演示

直接打开 `dist/index.html`。建议使用现代浏览器；摄像头功能通常需要通过 localhost 或 HTTPS 访问。

也可以在项目目录执行：

```bash
npx serve dist
```

演示流程：点击“开始自动巡检” → 点击“模拟异常” → 进入“告警中心”处理告警 → 切换“本机摄像头”展示真实接入能力。

## 发布到 GitHub Pages

仓库已包含 `.github/workflows/pages.yml`。推送到 `main` 分支后，GitHub Actions 会自动发布 `dist/` 目录；后续每次更新并推送都会自动重新部署。

## 技术架构

1. 感知层：ESP32-C3 连接 DHT22、MQ-2、INA219，采集环境与能耗数据。
2. 边缘层：Milk-V Duo 256M 连接 CSI 摄像头，运行轻量目标检测与规则引擎。
3. 通信层：MQTT/HTTP，采用统一 JSON 事件协议。
4. 平台层：Web 管理看板展示实时状态、告警和处置记录。

## 推荐硬件清单

| 设备 | 推荐型号 | 数量 | 用途 |
|---|---|---:|---|
| 感知主控 | ESP32-C3 | 1 | RISC-V 传感器采集与 Wi-Fi 通信 |
| 边缘计算板 | Milk-V Duo 256M | 1 | RISC-V Linux、1 TOPS INT8 边缘 AI 推理 |
| 摄像头 | 5MP MIPI CSI | 1 | 人员/烟雾/设备状态识别 |
| 温湿度传感器 | DHT22 | 1 | 环境监测 |
| 烟雾传感器 | MQ-2 | 1 | 烟雾与可燃气体监测 |
| 电流传感器 | INA219 | 1 | 设备功耗监测 |
| 声光模块 | 蜂鸣器 + LED | 1 | 本地告警 |

## 目录

- `dist/`：可直接运行的演示看板。
- `firmware/`：ESP32 传感节点参考固件。
- `hardware/`：硬件选型、接线定义、BOM 与原型制作说明。
- `edge/`：Milk-V Duo 边缘融合网关参考程序。
- `docs/`：项目方案、通信协议和答辩要点。

## 开源协议

本项目采用 MIT License。正式参赛前建议补充实物接线图、30 秒实机演示视频及真实测试数据。
