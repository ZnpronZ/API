using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;
using QuanLyAPI.Models;

namespace QuanLyAPI.Controllers
{
    [RoutePrefix("API/Products")]
    public class ProductsController : ApiController
    {
        QuanLyAPIDataContext db = new QuanLyAPIDataContext();

        [Route("GET/all")]
        [HttpGet]
        public IEnumerable<tblHang> getAllProducts()
        {
            IEnumerable<tblHang> listProdust = db.tblHangs.ToList();
            return listProdust;
        }

        [Route("GET/Item/{id}")]
        [HttpGet]
        public tblHang getItemOfProducts(string id)
        {
            tblHang item = db.tblHangs.Where(x => x.MaHang == id).FirstOrDefault();
            return item;
        }

        [Route("POST/Item")]
        [HttpPost]
        public bool insertItemOfProducts([FromBody]Products products)
        {
            try
            {
                tblHang item = new tblHang();
                    item.MaHang = products.MaHang;
                    item.CongTyDangKy = products.CongTyDangKy;
                    item.CongTySanXuat = products.CongTySanXuat;
                    item.TenHang = products.TenHang;
                    item.DangBaoChe = products.DangBaoChe;
                    item.HanSuDung = products.HanSuDung;
                    item.QuyCachDongGoi = products.QuyCachDongGoi;
                    item.GiaKeKhai = products.GiaKeKhai;
                    item.HoatChatHamLuong = products.HoatChatHamLuong;
                db.tblHangs.InsertOnSubmit(item);    
                db.SubmitChanges();
                    return true;
            }
            catch
            {
                return false;
            }
        }    

        [HttpPut]
        [Route("PUT/Item")]
        public bool editItemOfProducts([FromBody] Products products)
        {
            try
            {
                tblHang item = db.tblHangs.Where(n => n.MaHang == products.MaHang).FirstOrDefault();
                if(item!=null)
                {
                    item.MaHang = products.MaHang;
                    item.CongTyDangKy = products.CongTyDangKy;
                    item.CongTySanXuat = products.CongTySanXuat;
                    item.TenHang = products.TenHang;
                    item.DangBaoChe = products.DangBaoChe;
                    item.HanSuDung = products.HanSuDung;
                    item.QuyCachDongGoi = products.QuyCachDongGoi;
                    item.GiaKeKhai = products.GiaKeKhai;
                    item.HoatChatHamLuong = products.HoatChatHamLuong;
                    db.SubmitChanges();
                    return true;
                }
                return false;
                
            }
            catch
            {
                return false;
            }
        }

        [Route("DELETE/Item/{id}")]
        [HttpDelete]
        public bool deleteItemOfProducts(string id)
        {
            try
            {
                tblHang item = db.tblHangs.Where(n => n.MaHang == id).FirstOrDefault();
                if(item==null)
                {
                    return false;
                }
                db.tblHangs.DeleteOnSubmit(item);
                db.SubmitChanges();
                return true;
            }
            catch
            {
                return false;
            }
        }    
    }
}
