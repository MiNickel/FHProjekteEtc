using SGSE.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace SGSE.Services
{
    public interface IInvoiceService
    {
        Task<List<Invoice>> GetAll();
        Task<Invoice> GetById(string id);
        Task<Invoice> Create(Invoice invoice);
        Task Update(string id, Invoice invoice);
        Task Remove(Invoice invoice);
        Task RemoveById(string id);

        string GetPaypalAccessToken();
    }
}
