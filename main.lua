
function lea.onConfigure()
   lea.log("onConfig")
end

function lea.onInit()
   lea.log("onInit")

   icon = lea.icon.load("cactus.svg")
   tray = lea.tray.create(icon)
end

function lea.onQuit()
   lea.log("onQuit")
end
