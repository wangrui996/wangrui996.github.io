# modprobe  

* 第一次使用 modprobe 命令加载某个模块前，需要使用 depmod  命令 自动生成 modules.alias  modules.dep  modules.symbols 三个文件
* 然后再使用 modprobe xxxx.ko  

