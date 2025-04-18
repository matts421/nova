#include "animation_manager.hpp"
#include "common.hpp"          
#include <iostream>
#include <tinyECS/components.hpp>
#include <creature/creature_manager.hpp>


AnimationManager& AnimationManager::getInstance() {
    static AnimationManager instance;
    return instance;
}

// private construct
AnimationManager::AnimationManager() {
    initializeAnimations();
}


const AnimationDefinition* AnimationManager::getAnimation(const std::string& id) const {
    auto it = animations.find(id);
    if (it != animations.end()) {
        return &it->second;
    }
    // std::cerr << "AnimationManager: Animation not found for id: " << id << "\n";
    return nullptr;
}

const AnimationDefinition* AnimationManager::getCreatureAnimation(CreatureID creatureId, MotionAction action, MotionDirection direction) const {
    std::string key = buildCreatureAnimationKey(creatureId, action, direction);
    return getAnimation(key);
}

void AnimationManager::registerAnimation(const std::string& id, const AnimationDefinition& animDef) {
    animations[id] = animDef;
}

void AnimationManager::registerCreatureAnimation(CreatureID creatureId, MotionAction action, MotionDirection direction, const AnimationDefinition& animDef) {
    std::string key = buildCreatureAnimationKey(creatureId, action, direction);
    registerAnimation(key, animDef);
}

void AnimationManager::initializeAnimations() {
    animations.clear();

    SpriteSheet player_spritesheet;
    player_spritesheet.textureAssetID = TEXTURE_ASSET_ID::PLAYER;
    player_spritesheet.sheetDimensions = {152.f, 90.f};

    // --- Idle Animation ---
    AnimationDefinition idle_down;
    idle_down.id = buildAnimationKey(playerAnimationHeader(), MotionAction::IDLE, MotionDirection::DOWN);
    idle_down.loop = true;
    idle_down.frameWidth = PLAYER_SPRITESHEET.dims.x;
    idle_down.frameHeight = PLAYER_SPRITESHEET.dims.y;

    idle_down.spriteSheet = player_spritesheet;

    idle_down.frames.push_back({0, 0});
    idle_down.frameDurations.push_back(1000.f); 
    animations[idle_down.id] = idle_down;

    AnimationDefinition idle_up;
    idle_up.id = buildAnimationKey(playerAnimationHeader(), MotionAction::IDLE, MotionDirection::UP);
    idle_up.loop = true;
    idle_up.frameWidth = PLAYER_SPRITESHEET.dims.x;
    idle_up.frameHeight = PLAYER_SPRITESHEET.dims.y;

    idle_up.spriteSheet = player_spritesheet;

    idle_up.frames.push_back({2, 0});
    idle_up.frameDurations.push_back(1000.f); 
    animations[idle_up.id] = idle_up;

    AnimationDefinition idle_right;
    idle_right.id = buildAnimationKey(playerAnimationHeader(), MotionAction::IDLE, MotionDirection::RIGHT);
    idle_right.loop = true;
    idle_right.frameWidth = PLAYER_SPRITESHEET.dims.x;
    idle_right.frameHeight = PLAYER_SPRITESHEET.dims.y;

    idle_right.spriteSheet = player_spritesheet;

    idle_right.frames.push_back({1, 0});
    idle_right.frameDurations.push_back(1000.f); 
    animations[idle_right.id] = idle_right;

    // --- Walk Right Animation ---
    AnimationDefinition walkRight;
    walkRight.id = buildAnimationKey(playerAnimationHeader(), MotionAction::WALK, MotionDirection::RIGHT);
    walkRight.loop = true;
    walkRight.frameWidth = PLAYER_SPRITESHEET.dims.x;
    walkRight.frameHeight = PLAYER_SPRITESHEET.dims.y;
    walkRight.spriteSheet = player_spritesheet;


    for (int col = 0; col < 8; ++col) {
        walkRight.frames.push_back({1, col});
        walkRight.frameDurations.push_back(80.f); // 80 ms per frame.
    }
    animations[walkRight.id] = walkRight;

    // --- Walk Up Animation ---
    AnimationDefinition walkUp;
    walkUp.id = buildAnimationKey(playerAnimationHeader(), MotionAction::WALK, MotionDirection::UP);
    walkUp.loop = true;
    walkUp.frameWidth = PLAYER_SPRITESHEET.dims.x;
    walkUp.frameHeight = PLAYER_SPRITESHEET.dims.y;
    walkUp.spriteSheet = player_spritesheet;

    for (int col = 0; col < 8; ++col) {
        walkUp.frames.push_back({2, col});
        walkUp.frameDurations.push_back(80.f);
    }
    animations[walkUp.id] = walkUp;

    // --- Walk Down Animation ---
    AnimationDefinition walkDown;
    walkDown.id = buildAnimationKey(playerAnimationHeader(), MotionAction::WALK, MotionDirection::DOWN);
    walkDown.loop = true;
    walkDown.frameWidth = PLAYER_SPRITESHEET.dims.x;
    walkDown.frameHeight = PLAYER_SPRITESHEET.dims.y;
    walkDown.spriteSheet = player_spritesheet;

    for (int col = 0; col < 8; ++col) {
        walkDown.frames.push_back({3, col});
        walkDown.frameDurations.push_back(80.f);
    }
    animations[walkDown.id] = walkDown;
}
