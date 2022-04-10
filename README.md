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

lea.tray.create(icon)
lea.tray.delete(t)
lea.tray.setClickHandler(t, callback, userdata)
lea.tray.setScrollHandler(t, callback, userdata)

lea.icon.load(filename)

lea.timer.create(timeoutSeconds, shouldRepeat)
lea.timer.destroy(t)
lea.timer.resetTimeout(t, seconds)

lea.menu.create()
lea.menu.addSubMenu(m)
lea.menu.addItem(m, label, callback, userdata)
lea.menu.addSeparator(m)

lea.notification.create(title, message, icon)
lea.notification.addAction(nf, action, label, callback, userdata)
lea.notification.setTimeout(nf, seconds)

```
