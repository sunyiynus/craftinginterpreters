import gdb

class SpCmd(gdb.Command):
    def __init__(self):
        super(SpCmd, self).__init__("SpCmd", gdb.COMMAND_DATA)

    def invoke(self, arg, from_tty):
        print("Smp CMD exec");


class PrintListOf(gdb.Command):
    def __init__(self):
        super(PrintListOf, self).__init__("PrintListOf", gdb.COMMAND_DATA)

    def invoke(self, arg, from_tty):
        print(arg)
        res = gdb.parse_and_eval(arg)
        lstr = gdb.execute('p res.size()')
        #print(lstr.split('='))
        for i in range(100):
            print(res[i].dereference())

        #print(res)

SpCmd()
PrintListOf()
