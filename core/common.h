#ifndef COMMON_H
#define COMMON_H

#define ORIGINAL_NAME "Original"
#define DIFFERENTIAL_NAME "Differential"
#define INTEGRAL_NAME "Integral"

#define SETTING_PATH "setting.json"

#define MOVE_CONSTANT 0.5

#define DEFAULT_SETTING_CONTENT \
  "{ \
\"each_number\": 200, \
\"color\": { \
    \"Original\": [153, 102, 0], \
    \"Differential\": [204, 51, 0], \
    \"Integral\": [0, 102, 255] \
} \
}"

#endif  // COMMON_H
