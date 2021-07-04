using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;

namespace UngDungAPI.Controllers
{
    public class StudentsController : ApiController
    {
        //Get
        [HttpGet]
        public List<QLSV> GetSinhViens()
        {
            DbSinhVienDataContext dbStudents = new DbSinhVienDataContext();
            return dbStudents.QLSVs.ToList();
        }
        //Get
        [HttpGet]
        [Route("api/students/get/{Ma}")]
        public QLSV GetSinhViens(string Ma)
        {
            DbSinhVienDataContext dbStudents = new DbSinhVienDataContext();
            return dbStudents.QLSVs.Where(x => x.MaSV == Ma).FirstOrDefault();
        }
        //post
        [HttpPost]
        //[Route("api/students/post/")]
        public bool PostSinhVien(string Ma,string ten, string gioitinh,string adrr,int phone)
        {
            try
                {
                DbSinhVienDataContext dbStudents = new DbSinhVienDataContext();
                QLSV sinhvien = new QLSV();
                sinhvien.MaSV = Ma;
                sinhvien.HoTen = ten;
               
                sinhvien.DiaChi = adrr;
                sinhvien.GioiTinh = gioitinh;
                sinhvien.DienThoai = phone;

                
                dbStudents.QLSVs.InsertOnSubmit(sinhvien);
                dbStudents.SubmitChanges();
                return true;
            }
            catch 
            {
                return false;
            }
        }
        //put
        [HttpPut]
        public bool PutSinhVien(string Ma, string ten, string gioitinh, string adrr, int phone)
        {
            try
            {
                DbSinhVienDataContext dbStudents = new DbSinhVienDataContext();
                QLSV sinhvien = dbStudents.QLSVs.FirstOrDefault(x => x.MaSV == Ma);
                if (sinhvien == null) return false;
                sinhvien.MaSV = Ma;
                sinhvien.HoTen = ten;
               
                sinhvien.DiaChi = adrr;
                sinhvien.GioiTinh = gioitinh;
                sinhvien.DienThoai = phone;
                dbStudents.SubmitChanges();

                return true;
            }
            catch
            {
                return false;
            }
        }
        //delete
        [HttpDelete]
        [Route("api/students/delete/{Ma}")]
        public bool deleteSinhVien(string Ma)
        {
            try
            {
               DbSinhVienDataContext dbStudents = new DbSinhVienDataContext();
                QLSV sinhvien = dbStudents.QLSVs.FirstOrDefault(x => x.MaSV == Ma);
                if (sinhvien == null) return false;
                dbStudents.QLSVs.DeleteOnSubmit(sinhvien);
                dbStudents.SubmitChanges();
                return true;
            }
            catch
            {
                return false;
            }
        }
        }
}
