# Lea

Lua powered simple app engine.

## Features
- system tray icon
- notification
- svg icons


```lua

lea.onConfigure(conf)
lea.onInit()
lea.onQuit()

lea.quit()
lea.log(msg)

lea.Icon.load(filename)

lea.SystemTray.create(icon)
lea.SystemTray.onMousePress
lea.SystemTray.onMouseRelease
lea.SystemTray.onMouseScroll
lea.SystemTray:show()
lea.SystemTray:hide()

lea.Timer.create(timeoutSeconds, shouldRepeat)
lea.Timer:stop()
lea.Timer:reset(timeoutSeconds, shouldRepeat)
lea.Timer.onTimeout

lea.Menu.create()
lea.Menu:addItem(label, callback, userdata)
lea.Menu:addSeparator()
lea.Menu:addSubMenu(label)

lea.Notification.create(title, message, icon)
lea.Notification.show()
lea.Notification.icon
lea.Notification.onClick

```
