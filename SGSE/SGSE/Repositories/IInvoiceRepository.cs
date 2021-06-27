using SGSE.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace SGSE.Repositories
{
    public interface IInvoiceRepository
    {
        List<Invoice> GetAll();
        Invoice GetById(string id);
        Invoice Create(Invoice Invoice);
        void Update(string id, Invoice InvoiceIn);
        void Remove(Invoice InvoiceIn);
        void RemoveById(string id);
    }
}
