using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;

namespace ThucHanhAPI_1.Controller
{
    public class CustomersController : ApiController
    {
        //httpGet: dùng để lấy thông tin khách hàng
        //1. Dịch vụ lấy thông tin của toàn bộ khách hàng
        [HttpGet]
        public List<tblKhachHang> GetCustomerLists()
        {
            DBCustomersDataContext dbCustomer = new DBCustomersDataContext();
            return dbCustomer.tblKhachHangs.ToList();
        }
        //2. Dịch vụ lấy thông tin một khách hàng với mã nào đó
        [HttpGet]
        public tblKhachHang GetCustomer(string id)
        {
            DBCustomersDataContext dbCustomer = new DBCustomersDataContext();
            return dbCustomer.tblKhachHangs.FirstOrDefault(x => x.MaKH == id);
        }
        //3. httpPost, dịch vụ thêm mới một khách hàng
        [HttpPost]
        public bool InsertNewCustomer(string id, string name, string adress, string phoneNumber)
        {
            try
            {
                DBCustomersDataContext dbCustomer = new DBCustomersDataContext();
                tblKhachHang customer = new tblKhachHang();
                customer.MaKH = id;
                customer.TenKH = name;
                customer.DiaChi = adress;
                customer.DienThoai = phoneNumber;
                dbCustomer.tblKhachHangs.InsertOnSubmit(customer);
                dbCustomer.SubmitChanges();
                return true;
            }
            catch
            {
                return false;
            }
        }
        //4. httpPut để chỉnh sửa thông tin một khách hàng
        [HttpPut]
        public bool UpdateCustomer(string id, string name, string adress, string phoneNumber)
        {
            try
            {
                DBCustomersDataContext dbCustomer = new DBCustomersDataContext();
                //Lấy mã khách đã có
                tblKhachHang customer = dbCustomer.tblKhachHangs.FirstOrDefault(x => x.MaKH == id);
                if (customer == null) return false;
                customer.MaKH = id;
                customer.TenKH = name;
                customer.DiaChi = adress;
                customer.DienThoai = phoneNumber;
                dbCustomer.SubmitChanges();//Xác nhận chỉnh sửa
                return true;
            }
            catch
            {
                return false;
            }
        }
        //5.httpDelete để xóa một Khách hàng
        [HttpDelete]
        public bool DeleteCustomer(string id)
        {
            try
            {
                DBCustomersDataContext dbCustomer = new DBCustomersDataContext();
                //Lấy mã khách đã có
                tblKhachHang customer = dbCustomer.tblKhachHangs.FirstOrDefault(x => x.MaKH == id);
                if (customer == null) return false;
                dbCustomer.tblKhachHangs.DeleteOnSubmit(customer);
                dbCustomer.SubmitChanges();
                return true;
            }
            catch
            {
                return false;
            }
        }
    }
}
