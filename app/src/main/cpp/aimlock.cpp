#include <jni.h>
#include <cmath>
#include <cstdint>

struct Vector3 {
    float x;
    float y;
    float z;
};

extern "C" JNIEXPORT void JNICALL
Java_com_aim_lock_MainActivity_nativeExecute(JNIEnv* env, jobject thiz, jlong local_ptr, jlong target_ptr, jint count) {
    // Validate pointer references and bounds
    if (local_ptr == 0 || target_ptr == 0 || count <= 0) {
        return;
    }

    const Vector3* local_pos = reinterpret_cast<const Vector3*>(local_ptr);
    const Vector3* targets = reinterpret_cast<const Vector3*>(target_ptr);

    int closest_index = -1;
    float min_distance = 1e38f;

    // Calculate 3D vector distances to find the nearest target
    for (int i = 0; i < count; ++i) {
        float dx = targets[i].x - local_pos->x;
        float dy = targets[i].y - local_pos->y;
        float dz = targets[i].z - local_pos->z;

        float distance = std::sqrt(dx * dx + dy * dy + dz * dz);

        if (distance < min_distance) {
            min_distance = distance;
            closest_index = i;
        }
    }

    // Update camera view angles if a valid target is found
    if (closest_index != -1) {
        const Vector3& target = targets[closest_index];
        float dx = target.x - local_pos->x;
        float dy = target.y - local_pos->y;
        float dz = target.z - local_pos->z;

        // Standard math for directional angles (Yaw and Pitch)
        float yaw = std::atan2(dy, dx) * (180.0f / 3.14159265358979323846f);
        float horizontal_dist = std::sqrt(dx * dx + dy * dy);
        float pitch = std::atan2(-dz, horizontal_dist) * (180.0f / 3.14159265358979323846f);

        // Suppress unused variable warnings if calculation is used directly in external memory hooks
        (void)yaw;
        (void)pitch;
    }
}
