# MutantEFX — Psychic Mutant Effects

> Add fully configurable psychic abilities to any zombie, mutant, or animal in DayZ.

## 🌟 Overview

MutantEFX gives each entity type its own ability set, radius, chance, and cooldown — all defined in a JSON config that generates automatically on first launch.

Works with vanilla and modded entities alike. If it inherits from `ZombieBase` or `AnimalBase`, it will work. You can add as many different entity types to the config as you want, each with completely independent settings.

## ⚠️ Client & Server
This mod must be installed on **both the server and all clients**.

---

## 🧠 Abilities

### Psychic Blur
Players within range experience a visual distortion effect. Intensity and radius are configurable. Can be set to activate only when the entity is actively moving.

### Telekinesis Lift
The mutant launches nearby players into the air with a physics impulse. While airborne, the player's camera shakes. Height, duration, chance, and cooldown are all adjustable.

### Psychic Push
Players are thrown back with a directional impulse. The push direction originates from the mutant with a slight random yaw spread to feel less mechanical.

### Force Shoot
Forces the player to discharge their currently held weapon a configurable number of times in rapid succession.

### Drop Item
Rips the item out of a player's hands and drops it on the ground.

### Tick Damage
Passive health, blood, and shock damage applied at a configurable interval while the player remains within range.

### Death Flash
When the mutant is killed, a flashbang detonates at its position. Nearby players are blinded and knocked back. Radius and intensity are configurable.

### Forced Suicide
The mutant compels a player to perform the suicide animation, then kills them. Supports pistol, rifle, melee, and unarmed animations. A configurable HP threshold means this ability only triggers when the player is already weakened.

---

## ⚙️ Configuration

The config file is auto-generated on first launch at:

```
profiles/MutantEFX/MutantEFX_Config.json
```

You can define as many mutant entries as you want. **Delete the config file to regenerate defaults.**

### Example Entry

```json
{
  "classnames": ["YourCustomMutant"],
  "enabled": 1,
  "psychic_blur_enabled": 1,
  "psychic_blur_radius": 30.0,
  "psychic_blur_strength": 0.8,
  "psychic_blur_aggro_only": 0,
  "drop_item_enabled": 0,
  "drop_item_radius": 20.0,
  "drop_item_chance": 25.0,
  "drop_item_cooldown": 20.0,
  "force_shoot_enabled": 1,
  "force_shoot_count": 5,
  "force_shoot_radius": 25.0,
  "force_shoot_chance": 20.0,
  "force_shoot_cooldown": 25.0,
  "telekinesis_enabled": 1,
  "telekinesis_radius": 15.0,
  "telekinesis_lift_height": 3.5,
  "telekinesis_duration": 3.0,
  "telekinesis_chance": 15.0,
  "telekinesis_cooldown": 30.0,
  "psy_push_enabled": 1,
  "psy_push_radius": 20.0,
  "psy_push_force": 600.0,
  "psy_push_chance": 25.0,
  "psy_push_cooldown": 15.0,
  "death_flash_enabled": 1,
  "death_flash_radius": 25.0,
  "death_flash_intensity": 1.0,
  "death_knock_force": 500.0,
  "suicide_enabled": 1,
  "suicide_radius": 15.0,
  "suicide_chance": 8.0,
  "suicide_cooldown": 60.0,
  "suicide_hp_threshold": 100.0,
  "tick_interval": 5.0,
  "damage_health": 3.0,
  "damage_blood": 0.0,
  "damage_shock": 10.0,
  "damage_water": 0.0,
  "damage_energy": 0.0
}
```

---

## 📋 Parameter Reference

### General

| Parameter | Description |
|-----------|-------------|
| `classnames` | List of entity classnames this entry applies to |
| `enabled` | Enable/disable this entry (1/0) |

### Psychic Blur

| Parameter | Description |
|-----------|-------------|
| `psychic_blur_enabled` | Enable ability (1/0) |
| `psychic_blur_radius` | Effect radius (meters) |
| `psychic_blur_strength` | Blur intensity (0.0–1.0) |
| `psychic_blur_aggro_only` | Only activate while entity is moving (1/0) |

### Telekinesis Lift

| Parameter | Description |
|-----------|-------------|
| `telekinesis_enabled` | Enable ability (1/0) |
| `telekinesis_radius` | Activation radius (meters) |
| `telekinesis_lift_height` | Height players are launched to |
| `telekinesis_duration` | Duration of lift effect (seconds) |
| `telekinesis_chance` | Trigger chance (0–100) |
| `telekinesis_cooldown` | Cooldown between activations (seconds) |

### Psychic Push

| Parameter | Description |
|-----------|-------------|
| `psy_push_enabled` | Enable ability (1/0) |
| `psy_push_radius` | Activation radius (meters) |
| `psy_push_force` | Impulse force applied to players |
| `psy_push_chance` | Trigger chance (0–100) |
| `psy_push_cooldown` | Cooldown between activations (seconds) |

### Force Shoot

| Parameter | Description |
|-----------|-------------|
| `force_shoot_enabled` | Enable ability (1/0) |
| `force_shoot_count` | Number of forced shots |
| `force_shoot_radius` | Activation radius (meters) |
| `force_shoot_chance` | Trigger chance (0–100) |
| `force_shoot_cooldown` | Cooldown between activations (seconds) |

### Drop Item

| Parameter | Description |
|-----------|-------------|
| `drop_item_enabled` | Enable ability (1/0) |
| `drop_item_radius` | Activation radius (meters) |
| `drop_item_chance` | Trigger chance (0–100) |
| `drop_item_cooldown` | Cooldown between activations (seconds) |

### Tick Damage

| Parameter | Description |
|-----------|-------------|
| `tick_interval` | Damage interval (seconds) |
| `damage_health` | Health damage per tick |
| `damage_blood` | Blood damage per tick |
| `damage_shock` | Shock damage per tick |
| `damage_water` | Water damage per tick |
| `damage_energy` | Energy damage per tick |

### Death Flash

| Parameter | Description |
|-----------|-------------|
| `death_flash_enabled` | Enable ability (1/0) |
| `death_flash_radius` | Blast radius (meters) |
| `death_flash_intensity` | Flash brightness (0.0–1.0) |
| `death_knock_force` | Knockback impulse on nearby players |

### Forced Suicide

| Parameter | Description |
|-----------|-------------|
| `suicide_enabled` | Enable ability (1/0) |
| `suicide_radius` | Activation radius (meters) |
| `suicide_chance` | Trigger chance (0–100) |
| `suicide_cooldown` | Cooldown between activations (seconds) |
| `suicide_hp_threshold` | Max player HP for this ability to trigger |

---

## 📈 Scalability

- Add as many entity entries as needed — each with fully independent settings
- Works with **any** entity inheriting from `ZombieBase` or `AnimalBase`
- Compatible with all vanilla and modded entities

---

## 🚀 Installation

1. **Install the mod** on both your **server and all clients**
2. **Start the server** — the config file generates automatically
3. **Edit the config** at `profiles/MutantEFX/MutantEFX_Config.json`
4. **Restart the server** to apply changes

---

## 🔧 Supported Entities

MutantEFX works with **any living entity** that inherits from `ZombieBase` or `AnimalBase`, including:

- **Vanilla Zombies** — All `ZmbM_*`, `ZmbF_*` classes
- **Vanilla Animals** — All `Animal_*` classes
- **Modded Creatures** — Custom zombies, mutants, and animals from any mod
- **Custom NPCs** — Player-like entities or custom AI

---

## 🔍 Troubleshooting

**Abilities not triggering:**
- Verify `enabled` is set to `1` for the entry and the ability
- Check that the player is within the configured radius
- Ensure `chance` is not set to `0`

**Config not generating:**
- Start the server at least once with the mod active
- Check the `profiles/MutantEFX/` directory

**Wrong entities affected:**
- Double-check classnames are spelled correctly and match in-game classnames
- Use your server logs to verify the entity classname at spawn

---

## 📝 Credits & License

**Created by**: [Exodus DayZ Forge](https://discord.gg/pWd8adrm)  
**Original Author**: MrNicerDicer  
**Support**: Join our Discord for help and updates

This mod is free to use and modify. If you adapt or redistribute this code, please provide appropriate credit to the original creator.

---

**Created for DayZ 1.28 | Requires client & server install**