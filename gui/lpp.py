# This Python file uses the following encoding: utf-8
import sys
from PySide2.QtWidgets import QApplication


class LPP:
    def __init__(self):
        pass  # call __init__(self) of the custom base class here


if __name__ == "__main__":
    app = QApplication([])
    window = LPP()
    # window.show()
    sys.exit(app.exec_())
