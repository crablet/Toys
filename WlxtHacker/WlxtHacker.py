from splinter import Browser
from getpass import getpass
import time
import random

def Wait():
    time.sleep(random.uniform(0, 2))

ExecutablePath = input("Please your chromedriver.exe's path: ")
UserName = input("Please input your username: ")
Password = getpass("Please input your password: ")

Brs = Browser(driver_name="chrome", executable_path=ExecutablePath)
URL = "http://www.wlxt.uestc.edu.cn/wlxt/index.aspx"
Brs.visit(URL)
Wait()
Brs.find_by_id("hllogin").click()
Wait()
Brs.find_by_id("btnidaslogin").click()
Wait()
Brs.fill("username", UserName)
Wait()
Brs.fill("password", Password)
Wait()
Brs.find_by_text("登录").click()
Wait()
Brs.find_by_id("dataGridStudentCourse_imgbtnEnterCourseStudy_1").click()

for i in range(0, 100):
    Brs.visit(URL)
    time.sleep(random.uniform(0, 2))
    Brs.find_by_id("dataGridStudentCourse_imgbtnEnterCourseStudy_1").click()
    time.sleep(random.uniform(0, 2))

Brs.quit()