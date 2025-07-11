Originator（原发器）：负责创建/恢复状态快照
  |
  v
Memento（备忘录）：封装状态信息
  ^
  |
Caretaker（管理者）：负责保存/管理多个 Memento，不操作内容
