class GlobalLootItems
{
  string itemName;
  float  chance;
  int    quantity;

  void GlobalLootItems(string tItemName="", float tChance=0.0, int tQuantity=0)
  {
    itemName = tItemName;
    chance = tChance;
    quantity = tQuantity;
  }
}
