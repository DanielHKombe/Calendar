# 📅 C++ Calendar Application  

## 📌 Features  
- **Calendar Display**: View monthly layouts with current day highlighted  
- **Event Management**: Add, delete, and list events with reminders  
- **Navigation**:  
  - Switch months/years (`p`/`n` keys)  
  - Jump to specific dates (`s` key)  
  - Daily/weekly navigation (`<`/`>`, `u`/`b` keys)  
- **Data Persistence**:  
  - Auto-save events to `2.718281828459045235.txt`  
  - Export/import to custom files  
- **Input Validation**: Robust handling for dates/commands  

## 🛠️ Installation  
```bash
g++ main.cpp -o calendar -std=c++11 && ./calendar
```

## ⌨️ Command Reference  
| Key | Action                  | Example Usage          |  
|-----|-------------------------|------------------------|  
| `a` | Add event               | `a → 5 16 2025 "Meeting"` |  
| `d` | Delete event            | `d → [ID]`             |  
| `f` | Save to file            | `f → events_backup.txt`|  
| `g` | Go to event             | `g → [ID]`             |  
| `q` | Quit                    | `q` (Exits program)    |  

## 📂 File Format  
Saved events use this structure:  
```plaintext
[YEAR] [MONTH] [DAY]  
[Event Description]  
```

## 📜 License  
MIT License (see [LICENSE.txt](LICENSE.txt))  

