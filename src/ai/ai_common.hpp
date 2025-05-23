#pragma once

struct AIConfig {
    float detectionRange = 300.0f;
    float unchaseRange = 500.0f;
    float chaseSpeed = 100.0f;
    float attackRange = 50.0f;
    float patrolRadius = 100.0f;
    float patrolSpeed = 25.f;
    float patrolThreshold = 5.0f;

    float retreatRange = 0.0f; // 
    float retreatDistance = 0.0f; // distance to retreat from the player

    float attackCooldown = 0.0f; // cooldown between attacks
};