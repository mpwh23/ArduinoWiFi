**!!! working but some documentation is missing!!!**


## TODO
* fill this file

* add mac address
* add degugmode for println

def _print(*args):
    if AM_DEBUG_OUTPUT:
        line = ""
        for txt in args:
            line = line + " " + str(txt)
        if len(args) > 0:
            line += " > "
        print(line + inspect.stack()[1].__getattribute__("function"))