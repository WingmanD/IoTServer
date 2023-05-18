from conans import ConanFile

class Server(ConanFile):
    requires = "sqlite_orm/1.8.2", "drogon/1.8.3", "fmt/9.1.0"
    generators = "cmake"

    def configure(self):
        self.options["drogon"].with_ctl = True
