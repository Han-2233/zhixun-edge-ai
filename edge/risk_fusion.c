/*
 * 智巡开源：RISC-V 边缘风险融合参考程序
 * 在 Milk-V Duo 256M 上编译：gcc -O2 risk_fusion.c -o risk_fusion
 * 用法：./risk_fusion <temperature> <smoke_raw> <power_w> <vision_confidence>
 */
#include <stdio.h>
#include <stdlib.h>

static float clamp(float value, float low, float high) {
    return value < low ? low : (value > high ? high : value);
}

int main(int argc, char **argv) {
    if (argc != 5) {
        fprintf(stderr, "usage: %s temperature smoke_raw power_w vision_confidence\n", argv[0]);
        return 2;
    }

    const float temperature = (float)atof(argv[1]);
    const float smoke = (float)atof(argv[2]);
    const float power = (float)atof(argv[3]);
    const float vision = clamp((float)atof(argv[4]), 0.0f, 1.0f);

    const float temp_score = clamp((temperature - 30.0f) / 25.0f, 0.0f, 1.0f);
    const float smoke_score = clamp((smoke - 500.0f) / 1600.0f, 0.0f, 1.0f);
    const float power_score = clamp((power - 15.0f) / 25.0f, 0.0f, 1.0f);
    const float risk = 0.25f * temp_score + 0.40f * smoke_score
                     + 0.10f * power_score + 0.25f * vision;
    const char *level = risk >= 0.72f ? "high" : (risk >= 0.45f ? "medium" : "normal");

    printf("{\"risk\":%.3f,\"level\":\"%s\",\"localAlarm\":%s}\n",
           risk, level, risk >= 0.72f ? "true" : "false");
    return 0;
}
