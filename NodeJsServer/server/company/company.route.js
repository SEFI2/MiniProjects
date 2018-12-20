const express = require('express');
const validate = require('express-validation');
const paramValidation = require('../../config/param-validation');
const companyCtrl = require('./company.controller');

const router = express.Router(); // eslint-disable-line new-cap

router.route('/')
  /** GET /api/companies- Get list of companies */
  .get(companyCtrl.list)

  /** POST /api/companies - Create new company */
  .post(validate(paramValidation.createCompany), companyCtrl.create);

router.route('/:companyId')
  /** GET /api/companies/:companyId - Get company */
  .get(companyCtrl.get)

  /** PUT /api/companies/:companyId - Update company */
  .put(companyCtrl.update)

  /** DELETE /api/companies/:companyId - Delete ompany */
  .delete(companyCtrl.remove);

router.route('/details/:companyId')
    /** GET /api/companies/details/:companyId - Get company with list of coupons*/
    .get(companyCtrl.getDetails);

/** Load company when API with companyId route parameter is hit */
router.param('companyId', companyCtrl.load);

module.exports = router;
