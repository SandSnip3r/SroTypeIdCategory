#include "typeCategory.hpp"

#include <stdexcept>

// (MSB)                                                                       (LSB)
// | 15 | 14 | 13 | 12 | 11 | 10 | 09 | 08 | 07 | 06 | 05 | 04 | 03 | 02 | 01 | 00 |
// |         TypeID4        |       TypeID3     | TypeID2 |    TypeID1   |   N/A   |

namespace type_id {

TypeCategory::TypeCategory(uint8_t typeId1) : typeIdData_((typeId1 & static_cast<TypeId>(0b111)) << 2) {}

TypeCategory TypeCategory::subCategory(uint8_t nextTypeId) const {
  if (typeIdMask_ == kTypeId1Mask) {
    // Adding TypeId2 subcategory
    return TypeCategory{static_cast<TypeId>(typeIdData_ | ((nextTypeId & static_cast<TypeId>(0b11)) << 5)), kTypeId2Mask};
  } else if (typeIdMask_ == kTypeId2Mask) {
    // Adding TypeId3 subcategory
    return TypeCategory{static_cast<TypeId>(typeIdData_ | ((nextTypeId & static_cast<TypeId>(0b1111)) << 7)), kTypeId3Mask};
  } else /* if (typeIdMask_ == kTypeId3Mask) */ {
    // Adding TypeId4 subcategory
    return TypeCategory{static_cast<TypeId>(typeIdData_ | ((nextTypeId & static_cast<TypeId>(0b11111)) << 11)), kTypeId4Mask};
  }
  throw std::runtime_error("Cannot add another subcategory");
}

bool TypeCategory::contains(TypeId typeId) const {
  return (typeId & typeIdMask_) == (typeIdData_ & typeIdMask_);
}

} // namespace type_id