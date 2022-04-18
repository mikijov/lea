# Lea

> Lua powered, simple and lightweight app engine.

## Features
- Script using [Lua](https://www.lua.org/).
- System tray icon.
- Notifications.
- Dynamic menus.
- Timers.

## Lua Programming

### Hello, World.
This script will
```lua
function onInit()
  lea.log("Hello, World.\n")
  lea.quit()
end
```

### Main Callbacks
Upon startup, Lea will load your Lua file. Then it will call onConfigure() if it
exists, allowing your code to configure the runtime. Once initialised, it will
call onInit() where you should initialise your application and any widgets or
features you need. Depending on your initialisation, Lea will process events
from the user and appropriately call any other callbacks you have registered.
Whenever your application needs to exit, call lea.quit(). Just before quitting,
Lea will call onQuit(), where you can save state or do any other required
cleanup.

```lue
function lea.onConfigure(config)
  -- modify config any way you require
end

function lea.onInit()
  -- setup any UI and register callbacks
end

function lea.onQuit()
  -- save state and do any required cleanup
end
```

### Lua API

#### lea namespace
```lua

lea.onConfigure(conf)
lea.onInit()
lea.onQuit()

lea.quit()
lea.log(msg)
```

#### Icon
```lua
lea.Icon.load(filename)
```

#### SystemTray
```lua
lea.SystemTray.create(icon)
lea.SystemTray.onMousePress
lea.SystemTray.onMouseRelease
lea.SystemTray.onMouseScroll
lea.SystemTray:show()
lea.SystemTray:hide()
```

#### Timer
```lua
lea.Timer.create(timeoutSeconds, shouldRepeat)
lea.Timer:stop()
lea.Timer:reset(timeoutSeconds, shouldRepeat)
lea.Timer.onTimeout
```

#### Menu
```lua
lea.Menu.create()
lea.Menu:addItem(label, callback, userdata)
lea.Menu:addSeparator()
lea.Menu:addSubMenu(label)
```

#### Notification
```lua
lea.Notification.create(title, message, icon)
lea.Notification.show()
lea.Notification.icon
lea.Notification.onClick
```
