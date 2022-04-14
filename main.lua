
function onMousePress(tray)
   lea.log("onMousePress called")
end

function onMouseRelease(tray)
   lea.log("onMouseRelease called")
   lea.quit()
end

function onMouseScroll(tray)
   lea.log("onMouseScroll called")
end

function lea.onConfigure()
   lea.log("onConfigure")
end

-- function myTest()
--    lea.
-- end

function lea.onInit()
   lea.log("onInit")

   local icon = lea.Icon.load("../cactus.svg")
   local tray = lea.SystemTray.create(icon)
   tray.onMousePress = onMousePress
   tray.onMouseRelease = onMouseRelease
   tray.onMouseScroll = onMouseScroll
end

function lea.onQuit()
   lea.log("onQuit")
end

-- mousePress(nil, "hi")
-- lea.log("standalone")

