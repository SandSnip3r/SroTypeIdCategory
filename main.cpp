#include "categories.hpp"
#include "typeCategory.hpp"

#include <iostream>
#include <optional>
#include <vector>

using namespace std;

// Type Ids:
//  1: Character
//    1: PlayerCharacter
//    2: NonPlayerCharacter
//      1: Monster
//        1: Standard
//        4: Quest
//      2: NPC
//      3: Pet
//  3: Item
//    1: Equipment
//      1: Garment
//      2: Protector
//      3: Armor
//      4: Shield
//      5: Accessory
//      6: Weapon
//        2: Sword
//        3: Blade
//        4: Spear
//        7: One-handed Sword
//        8: Two-handed Sword
//        9: Dual Axe
//    3: Expendable
//      1: Recovery Potion
//        1: HP Potion
//        2: MP Potion
//      2: Cure Potion
//        1: Purification Pill
//        7: Universal Pill

class Item {
public:
  Item(uint8_t typeId1, uint8_t typeId2, uint8_t typeId3, uint8_t typeId4) : typeId_(((typeId4 & static_cast<type_id::TypeId>(0b11111)) << 11) | ((typeId3 & static_cast<type_id::TypeId>(0b1111)) << 7) | ((typeId2 & static_cast<type_id::TypeId>(0b11)) << 5) | ((typeId1 & static_cast<type_id::TypeId>(0b111)) << 2)) {}
  bool isA(const type_id::TypeCategory &typeCategory) const {
    return typeCategory.contains(typeId_);
  }
private:
  uint16_t typeId_;
};

int main() {
  auto test = [](const Item &item, const auto category, const std::string &categoryName) {
    if (item.isA(category)) {
      std::cout << "Is an " << categoryName << std::endl;
    } else {
      std::cout << "Is NOT an " << categoryName << std::endl;
    }

  };
  
  Item sword(3,1,6,2);
  test(sword, type_id::categories::kEquipment, "Equipment");
  test(sword, type_id::categories::kWeapon, "Weapon");
  test(sword, type_id::categories::kGarment, "Garment");
  test(sword, type_id::categories::kStandardMonster, "StandardMonster");
  std::cout << std::endl;

  Item monster(1,2,1,1);
  test(monster, type_id::categories::kEquipment, "Equipment");
  test(monster, type_id::categories::kWeapon, "Weapon");
  test(monster, type_id::categories::kGarment, "Garment");
  test(monster, type_id::categories::kStandardMonster, "StandardMonster");
  return 0;
}